//#include "ap_axi_sdata.h" // ap_axis can also be used, but it will include all sideband signals which we don't need
//#include "definition.h"
#include "ap_int.h"
#include "math_functions.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "hard_def.h"
// Creating a custom structure which includes the data word and TLAST signal.
// ACLK, ARESETN, TREADY, TDATA, TVALID are essential signals for AXIS.
// TLAST is a sideband signal which is optional in AXIS.
// However, it is necessary for us since we connecting M_AXIS to AXI Stream FIFO / AXI DMA.
// So, we create a struct with data (TDATA) and last (TLAST). The rest of the essential AXIS signals are automatically dealt with by the HLS tool.

//#define NUMBER_OF_INPUT_WORDS 4  // length of an input vector
//#define NUMBER_OF_OUTPUT_WORDS 4  // length of an input vector

struct AXIS_wLAST{
	DTYPE data;
	bool last;
};


void hard_cnn(hls::stream<AXIS_wLAST>& S_AXIS, hls::stream<AXIS_wLAST>& M_AXIS){
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=S_AXIS
#pragma HLS INTERFACE axis port=M_AXIS
	DTYPE input[NUM_INPUT];
	DTYPE hidden_layer_0[NUM_LAYER_0];
	DTYPE hidden_layer_1[NUM_LAYER_1];
	DTYPE output_layer[NUM_OUTPUT];
	DTYPE softmax_layer[NUM_OUTPUT];
	//DTYPE correct = 0;
	//DTYPE percentage = 0;
	//DTYPE num_trainings = 0;

	neuron<DTYPE, NUM_INPUT, NUM_LAYER_0, 0> imm_neuron_1;
	neuron<DTYPE, NUM_LAYER_0, NUM_LAYER_1, 0> imm_neuron_2;
	neuron<DTYPE, NUM_LAYER_1, NUM_OUTPUT, 0> out_neuron;


	//defining learning rate
	//float STEP = 0.02;
//	int LEARN_RATE_SHIFT = 4;
	int training_mode = 0;
	DTYPE count;
	AXIS_wLAST in, out;
	int stage = 2;
			//in = S_AXIS.read();
			//training_mode = in.data;
			//correct = 0;
			//out.last = false;
			retrieve_inputs:for (int i = 0; i < NUM_INPUT; i++) {
				in = S_AXIS.read();
				input[i] = in.data;
			}
			out.last = false;
			//DTYPE val;
			normalization:for (int i = 0; i < NUM_INPUT; i++) {
				if (std_dev[i] != 0) {
					input[i] = (input[i] - mean[i])/std_dev[i];
				}
			}
			//Original input is input of layer_0
			layer0:for (int i = 0; i < NUM_LAYER_0; i++) {
				#pragma HLS pipeline
				count = 0;
				//val = imm_neuron_1.dot_product(input, weights_0, i);
				for (int j = 0; j < NUM_INPUT; j++) {
					#pragma HLS unroll
					count += input[j]*weights_0[j][i];
				}
				count += layer_0_bias[i];
				hidden_layer_0[i] = relu_func<DTYPE>(count);
			}

			//Hidden layer_0's output is input of layer_1
			layer_1:for (int i = 0; i < NUM_LAYER_1; i++) {
				#pragma HLS pipeline
				count = 0;
				for (int j = 0; j < NUM_LAYER_0; j++) {
					#pragma HLS unroll
					count += hidden_layer_0[j]*weights_1[j][i];
				}
				count += layer_1_bias[i];
				//val =imm_neuron_2.dot_product(hidden_layer_0, weights_1, i);
				hidden_layer_1[i] = relu_func<DTYPE>(count);
			}

			layer_out:for (int i = 0; i < NUM_OUTPUT; i++) {
				#pragma HLS pipeline
				count = 0;
				for (int j = 0; j < NUM_LAYER_1; j++) {
					#pragma HLS unroll
					count += hidden_layer_1[j]*output_weights[j][i];
				}
				count += output_bias[i];
				//val = out_neuron.dot_product(hidden_layer_1, output_weights, i);
				output_layer[i] = relu_func<DTYPE>(count);
			}

			/*for (int i = 0; i < NUM_OUTPUT; i++) {
				#pragma HLS pipeline
				//out_neuron.dot_product(hidden_layer_1, weights_1[i], val);
				softmax_layer[i] = out_neuron.softmax_out(output_layer, i);
			}*/
			DTYPE exp_sum = 0;
			for (int i = 0; i < NUM_OUTPUT; i++) {
				#pragma HLS unroll
				exp_sum += exp(output_layer[i]);
			}
			//If training mode is specified, we proceed to weights, biases modifications
				//percentage = correct/NUM_OUTPUT;
				//out.data = correct;
			int max = 0;
			for (int i = 1; i< NUM_OUTPUT; i ++) {
				#pragma HLS pipeline
				if (output_layer[i] > output_layer[max]) {
					max = i;
				}
				//DTYPE prob = 100*(DTYPE(exp(output_layer[max]))/(DTYPE)exp_sum);
				//int prob_int =  (int)(prob);
				//out.data = prob_int;
				//M_AXIS.write(out);
				//out.data =DTYPE(max + 1) + prob;
				/*out.data = output_layer[i];
				if (i == NUM_OUTPUT - 1) {
					out.last = true;
				}
				M_AXIS.write(out);*/
				if (i == NUM_OUTPUT - 1) {
					out.data = max;
					M_AXIS.write(out);
					DTYPE prob = 100*(DTYPE(exp(output_layer[max]))/(DTYPE)exp_sum);
					int prob_int =  (int)(prob);
					out.data = prob_int;
					//out.data = prob_int;
					out.last = true;
					M_AXIS.write(out);
				}
			}
			/*DTYPE prob = 100*(DTYPE(exp(output_layer[max]))/(DTYPE)exp_sum);
			int prob_int =  (int)(prob);
			out.data = max;
			M_AXIS.write(out);
			out.data = prob_int;
			out.last = true;
			M_AXIS.write(out);*/
			/*out.data = output_layer[max];
			M_AXIS.write(out);*/
			//out.data = prob_int;
			//out.last = true;
			////M_AXIS.write(out);
			////out.data =max;
			////out.last = true;
			////M_AXIS.write(out);
}
