"""
Python script to send things via dma to Ultra96's FPGA

Author: Ivander, Jusuf, Minh Thong
"""
import numpy as np
import math
import time

from pynq import Overlay
from pynq import allocate

from multiprocessing import Queue, Pipe, Process

OVERLAY = None
DMA = None
BITSTREAM_FILE_NAME = 'bitstreams/W13_V0.bit'



INPUT_DIM = 5 * 3
LAYER1_DIM = 30
LAYER2_DIM = 10
OUTPUT_DIM = 8

def get_weights(npfile):
    return [list(weight) for weight in list(npfile)]

def get_biases(npfile):
    return list(npfile)

weight0 = get_weights(np.load("weights/weight_0.npy"))
weight1 = get_weights(np.load("weights/weight_1.npy"))
weight2 = get_weights(np.load("weights/weight_out.npy"))
bias0 = get_biases(np.load("weights/bias_0.npy"))
bias1 = get_biases(np.load("weights/bias_1.npy"))
bias2 = get_biases(np.load("weights/bias_out.npy"))

mean = np.load("weights/mean.npy")
std = np.load("weights/std.npy")

print("[ML DMA] Done loading weights")

def calculate(prescaled_data):
	temp = np.subtract(prescaled_data, mean)
    features = np.divide(temp, std, out=np.zeros_like(temp), where=std!=0)
    features = features[0]

    input_layers = [0 for i in range(LAYER1_DIM)]
    for i in range(LAYER1_DIM):
        count = 0
        for j in range(INPUT_DIM):
            count += features[j] * weight0[j][i]
        count += bias0[i]
        input_layers[i] = max(0, count)

    hidden_layers = [0 for i in range(LAYER2_DIM)]
    for i in range(LAYER2_DIM):
        count = 0
        for j in range(LAYER1_DIM):
            count += input_layers[j] * weight1[j][i]
        count += bias1[i]
        hidden_layers[i] = max(0, count)

    output_layers = [0 for i in range(OUTPUT_DIM)]
    for i in range(OUTPUT_DIM):
        count = 0
        for j in range(LAYER2_DIM):
            count += hidden_layers[j] * weight2[j][i]
        count += bias2[i]
        output_layers[i] = max(0, count)

    exp_list = [math.exp(i) for i in output_layers]
    probabilities = [i / sum(exp_list) for i in exp_list]
    return probabilities, np.argmax(probabilities)



# -------------------- DMA --------------------------#

def load_overlay():
    global OVERLAY, DMA

    print(f"Loading overlay {BITSTREAM_FILE_NAME}")
    OVERLAY = Overlay(BITSTREAM_FILE_NAME)
    DMA = OVERLAY.axi_dma_0
    print(f"DMA object: {DMA}")

def mock_ml_dma_process(in_p, dash_q, eval_q):
    while True:
        data = in_p.recv()

        id = data[0]
        features = data[1]

        result = calculate(features)
        print("##### MOCK DMA PROCESS #####")
        print(result, {'cmd': 'ml_dma', 'val': [id, result[1], result[0][result[1]]]})
        print("############################")
        eval_q.put({'cmd': 'move', 'val': [id, result[1], result[0][result[1]]]})
        dash_q.put({'cmd': 'ml_dma', 'val': [id, result[1], result[0][result[1]]]})

def ml_dma_process(in_p, dash_q, eval_q):

    load_overlay()

    while True:
        # Receiving data from pipe
        # is a 1 dimensional python list of length 15
        data = in_p.recv()

        id = data[0]
        features = data[1][0]
        features[8] = 1
        features[13] = 1

        print("##### REAL DMA PROCESS #####")
        print(f"TO DMA dancer:{id} featrs:{np.array_str(np.array(features), precision=3)}")

        # Sending data from pipe
        input_buffer = allocate(shape=(INPUT_DIM,), dtype = np.float32)
        output_buffer = allocate(shape=(2,), dtype = np.float32)

        # features data is in the form of a 2d array.
        # e.g. [0 + prob(1), 1 + prob(2), 2 + prob(3)]
        for idx, x in np.ndenumerate(features):
            input_buffer[idx] = x

        print(f"■ >>> Sending input buffers to DMA")
        DMA.sendchannel.transfer(input_buffer)
        DMA.recvchannel.transfer(output_buffer)
        DMA.sendchannel.wait()
        DMA.recvchannel.wait()
                fpga_res = np.zeros(2)
        fpga_res = np.column_stack(output_buffer)
        print(f"□ <<< Received results array: {fpga_res}")

        pred_move_id = fpga_res[0][0] // 1
        pred_accuracy = fpga_res[0][1] / 100.0

        value = [id, pred_move_id, pred_accuracy]
        print(f"VALUE = {value}")

        del input_buffer, output_buffer

        eval_q.put({'cmd': 'move', 'val': value})
        dash_q.put({'cmd': 'ml_dma', 'val': value})

        print("############################")


## MAIN FUNCTION
if __name__ == "__main__":
    import pandas as pd

    CSV_FILE = 'test_data.csv'
    df = pd.read_csv(CSV_FILE).to_numpy()

    features_ml, features_dma = Pipe()
    features_ml_mock, features_dma_mock = Pipe()
    prediction_ml_eval = Queue()
    dash_q = Queue()
    Process(target=ml_dma_process, args=(features_dma, dash_q, prediction_ml_eval)).start()
    Process(target=mock_ml_dma_process, args=(features_dma_mock, dash_q, prediction_ml_eval)).start()

    time.sleep(3)
    for row in df:
        arr = row
        features_ml.send([1,arr])
        features_ml_mock.send([1,arr])
        time.sleep(1)