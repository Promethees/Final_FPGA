#include "xparameters.h"
#include "xil_exception.h"
#include "xstreamer.h"
#include "xil_cache.h"
#include "xllfifo.h"
#include "xstatus.h"
#include "test_def.h"
#include "C:\Users\e0407640\Desktop\HLS_scripts\hard_def.h"
#include "C:\Users\e0407640\Desktop\HLS_scripts\definition.h"
#include "C:\Users\e0407640\Desktop\HLS_scripts\math_functions.h"

/***************** Macros *********************/
#define NUMBER_OF_INPUT_WORDS 15  // length of an input vector
#define NUMBER_OF_OUTPUT_WORDS 3  // length of an input vector
#define NUMBER_OF_TEST_VECTORS 8  // number of such test vectors (cases)

#define FIFO_DEV_ID	   	XPAR_AXI_FIFO_0_DEVICE_ID

/************************** Variable Definitions *****************************/
u16 DeviceId = FIFO_DEV_ID;
XLlFifo FifoInstance; 	// Device instance
XLlFifo *InstancePtr = &FifoInstance; // Device pointer

int test_input_memory [NUMBER_OF_TEST_VECTORS*NUMBER_OF_INPUT_WORDS] = {0x01, 0x02, 0x03, 0x04, 0x02, 0x03, 0x04, 0x05}; // 4 inputs * 2
int test_result_expected_memory [NUMBER_OF_TEST_VECTORS*NUMBER_OF_OUTPUT_WORDS];// 4 outputs *2
int result_memory [NUMBER_OF_TEST_VECTORS*NUMBER_OF_OUTPUT_WORDS]; // same size as test_result_expected_memory

/*****************************************************************************
* Main function
******************************************************************************/
int main()
{
	int Status;
	int word_cnt, test_case_cnt = 0;
	int success;
	Status = XST_SUCCESS;

	/************************** Initializations *****************************/
	XLlFifo_Config *Config;

	/* Initialize the Device Configuration Interface driver */
	Config = XLlFfio_LookupConfig(DeviceId);
	if (!Config) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

	Status = XLlFifo_CfgInitialize(InstancePtr, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed\r\n");
		return XST_FAILURE;
	}

	/* Check for the Reset value */
	Status = XLlFifo_Status(InstancePtr);
	XLlFifo_IntClear(InstancePtr,0xffffffff);
	Status = XLlFifo_Status(InstancePtr);
	if(Status != 0x0) {
		xil_printf("\n ERROR : Reset value of ISR0 : 0x%x\t. Expected : 0x0\r\n",
			    XLlFifo_Status(InstancePtr));
		return XST_FAILURE;
	}

	/************** Run a software version of the hardware function to validate results ************/
	// done instead of hard-coding the results in test_result_expected_memory
	// int sum;
	// for (test_case_cnt=0 ; test_case_cnt < NUMBER_OF_TEST_VECTORS ; test_case_cnt++){
	// 	sum = 0;
	// 	for (word_cnt=0 ; word_cnt < NUMBER_OF_INPUT_WORDS ; word_cnt++){
	// 		sum +=test_input_memory[word_cnt+test_case_cnt*NUMBER_OF_INPUT_WORDS];
	// 	}
	// 	for (word_cnt=0; word_cnt < NUMBER_OF_INPUT_WORDS; word_cnt++) {
	// 		test_result_expected_memory[word_cnt+test_case_cnt*NUMBER_OF_OUTPUT_WORDS] = sum;
	// 	}
	// }
	DTYPE input[NUM_INPUT];
	DTYPE hidden_layer_0[NUM_LAYER_0];
	DTYPE hidden_layer_1[NUM_LAYER_1];
	DTYPE output_layer[NUM_OUTPUT];
	DTYPE softmax_layer[NUM_OUTPUT];
	for (test_case_cnt = 0; test_case_cnt < NUMBER_OF_TEST_VECTORS; test_case_cnt ++) {
		retrieve_inputs:for (int i = 0; i < NUM_INPUT; i++) {
			input[i] = test_features[test_case_cnt* NUM_INPUT + i];
		}
		//DTYPE val;

		//normalization
		for (int i = 0; i < NUM_INPUT; i++) {
			input[i] = (input[i] - mean[i])/standard[i];
		}
		//Original input is input of layer_0
		layer0:for (int i = 0; i < NUM_LAYER_0; i++) {
			#pragma HLS pipeline
			int count = 0;
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

		DTYPE exp_sum = 0;
		for (int i = 0; i < NUM_OUTPUT; i++) {
			#pragma HLS unroll
			exp_sum += exp(output_layer[i]);
		}

		for (int word_cnt = 1; word_cnt< NUMBER_OF_OUTPUT_WORDS; word_cnt ++) {
			DTYPE prob = 100*(DTYPE(exp(output_layer[max]))/(DTYPE)exp_sum);
			//int prob_int =  (int)(prob);
			//out.data = prob_int;M_AXIS.write(out);
			//int prob_int = int(prob);
			test_result_expected_memory[test_case_cnt*NUMBER_OF_OUTPUT_WORDS + word_cnt] = prob;

		}

	}



	for (test_case_cnt=0 ; test_case_cnt < NUMBER_OF_TEST_VECTORS ; test_case_cnt++){

		/************************** Output : Transmit the Data Stream *****************************/

		xil_printf(" Transmitting Data for test case %d ... \r\n", test_case_cnt);

		/* Writing into the FIFO Transmit Port Buffer */
		for (word_cnt=0 ; word_cnt < NUMBER_OF_INPUT_WORDS ; word_cnt++){
			if( XLlFifo_iTxVacancy(InstancePtr) ){
				XLlFifo_TxPutWord(InstancePtr, test_input_memory[word_cnt+test_case_cnt*NUMBER_OF_INPUT_WORDS]);
			}
		}

		/* Start Transmission by writing transmission length (number of bytes = 4* number of words) into the TLR */
		XLlFifo_iTxSetLen(InstancePtr, NUMBER_OF_INPUT_WORDS * 4);

		/* Check for Transmission completion */
		while( !(XLlFifo_IsTxDone(InstancePtr)) ){

		}
		/* Transmission Complete */

		/************************** Input : Receive the Data Stream *****************************/
		/* Receive the Data Stream */
		xil_printf(" Receiving data for test case %d ... \r\n", test_case_cnt);

		while(XLlFifo_iRxOccupancy(InstancePtr)) {
			// Number of words received = number of bytes received / 4
			u32 ReceiveLength = XLlFifo_iRxGetLen(InstancePtr)/4;
			for (word_cnt=0; word_cnt < ReceiveLength; word_cnt++) {
				// read one word at a time
				result_memory[word_cnt+test_case_cnt*NUMBER_OF_OUTPUT_WORDS] = XLlFifo_RxGetWord(InstancePtr);
			}
		}

		Status = XLlFifo_IsRxDone(InstancePtr);
		if(Status != TRUE){
			xil_printf("Failing in receive complete ... \r\n");
			return XST_FAILURE;
		}
		/* Reception Complete */
	}

	/************************** Checking correctness of results *****************************/

	success = 1;

	/* Compare the data send with the data received */
	xil_printf(" Comparing data ...\r\n");
	for(word_cnt=0; word_cnt < NUMBER_OF_TEST_VECTORS*NUMBER_OF_OUTPUT_WORDS; word_cnt++){
		success = success & (result_memory[word_cnt] == test_result_expected_memory[word_cnt]);
	}

	if (success != 1){
		xil_printf("Test Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Test Success\r\n");

	return XST_SUCCESS;
}
