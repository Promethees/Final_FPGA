#include "ap_fixed.h"
#include <math.h>
#include <assert.h>
#include "definition.h"
template <class T, int size_in, int col_size, int offset> class neuron {
public:
	T a_int[size_in],b_int[size_in];
	neuron() {
	}

	//This function calculating the dot product of vector_array a[size_in] and vector_array b[size_in]
	//out is the value to be passed in function
	T dot_product(T a[size_in], T b[size_in][col_size], int index) {
		#pragma HLS array_partition variable=a_int complete
		#pragma HLS array_partition variable=b_int complete
		T product = 0;

		for(int i = 0; i < size_in; i++) {
			#pragma HLS pipeline
			a_int[i] = a[i+offset];
		}
		for(int i = 0; i < size_in; i++) {
			#pragma HLS pipeline
			b_int[i] = b[i+offset][index];
		}

		for(int i = 0; i < size_in; i++) {
			#pragma HLS unroll
			product += a_int[i] * b_int[i];
		}
		return product;
	}
	T softmax_out(T a[size_in], int index) {
		T sum = 0;
		sum = exp_sum(a);
		T nume = exp(a[index]);
		T out = (float)exp(a[index])/(float)sum;
		return out;
	}
	T exp_sum(T a[size_in]) {
		T sum = 0;
		for (int i = 0; i < size_in; i++) {
			#pragma HLS unroll
			sum += exp(a[i]);
		}
		return sum;
	}
	/*void cross_entropy(T a[size_in], T b[size_in], T &out) {
		T sum = 0;
		for (int i = 0; i < size_in; i++) {
			#pragma HLS unroll
			sum += -a[i]*log(b[i]);
		}
		out = sum;
	}*/
};

template <class T>
T relu_func(T a) {
	if (a > 0) {
		return a;
	} else {
		return 0;
	}
};

template <class T>
T sigmoid(T a) {
	return 1/(1 + exp(-a));
}

template <class T>
T dSigmoid(T a) {
	return a*(1-a);
}

DTYPE roundbit(float f, int bits) {
  union { int i; float f; } num;

  bits = 32 - bits ;
  // assuming sizeof(int) == sizeof(float) == 4
  num.f = f;
  num.i = num.i + (1 << (bits - 1)); // round instead of truncate
  num.i = num.i & (-1 << bits);
  return num.f;
}

/*template <class T>
T softmax(T* input, int size) {
	assert(0 <= size <= sizeof(input) / sizeof(T));

	T m, sum, constant;
	m = -INFINITY;

	//find the minimum element
	for (int i = 0; i < size; i ++) {
		#pragma HLS pipeline
		if (m < input[i]) {
			m = input[i];
		}
	}

	sum = 0.0;
	for (int i = 0; i < size; i++) {
		#pragma HLS unroll
		sum += exp(input[i] - m);
	}

	constant = m + log(sum);
	for (int i = 0; i < size; ++i) {
		#pragma HLS unroll
		input[i] = exp(input[i] - constant);
	}
}
*/

