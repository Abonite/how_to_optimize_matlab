#include "Complex.h"

// #include <mex.h>
#define _USE_MATH_DEFINES
#include <math.h>


int* bin_reverse(int fft_layer) {
    int size = (int) pow(2.0, (double) fft_layer);
    int* reversed = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        int temp = 0;
        for (int j = 0; j < fft_layer; j++) {
            temp |= ((i >> j) & 1) << (fft_layer - 1 - j);
        }
        reversed[i] = temp;
    }
    return reversed;
}

Complex* butterfly(Complex i1, Complex i2, Complex W) {
    Complex* output = (Complex*)malloc(2 * sizeof(Complex));

    Complex T = mulComplex(W, i2);
    output[0] = addComplex(i1, T);
    output[1] = subComplex(i1, T);

    return output;
}

Complex* subo(Complex* source_points, int source_points_length, int gap) {
    int loop_t = source_points_length >> 1;
    Complex* output = (Complex*)malloc(source_points_length * sizeof(Complex));
    int N = gap << 1;
    for (int i = 0; i < loop_t; i++) {
        Complex W = newComplexPolar(1.0, (double) i * -1.0 * M_PI / N);
        Complex* temp = butterfly(source_points[i], source_points[i + gap], W);
        output[i] = temp[0];
        output[i + loop_t] = temp[1];
        free(temp);
    }
    return output;
}

Complex* my_fft_cvar(Complex* input, int n, int fft_layer) {
    // This is a placeholder for the actual FFT implementation.
    // For demonstration purposes, we'll just return the input array.
    Complex* middle_vectory = (Complex*)malloc(n * sizeof(Complex));
    int* bin_reversed_seq = bin_reverse(n);
    for (int i = 0; i < n; i++) {
        middle_vectory[i] = input[bin_reversed_seq[i]];
    }
    free(bin_reversed_seq);

    for (int i = 0; i < fft_layer; i++) {
        int gap = (int) pow(2.0, (double) i);
        int sub_l = (int) pow(2.0, (double) (i + 1));
        for (int j = 0; j < n; j += 2 * gap) {
            Complex* temp = subo(&middle_vectory[j], sub_l, gap);
            for (int k = 0; k < sub_l; k++) {
                middle_vectory[j + k] = temp[k];
            }
            free(temp);
        }
    }
    return middle_vectory;
}

// void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // if (nrhs != 2) {
        // mexErrMsgIdAndTxt("MyFFT:InvalidNumInputs", "Two inputs required.");
    // }
    // if (nlhs != 1) {
        // mexErrMsgIdAndTxt("MyFFT:InvalidNumOutputs", "One output required.");
    // }
// 
    // if (!mxIsDouble(prhs[0]) || mxIsComplex(prhs[0]) || mxGetNumberOfDimensions(prhs[0]) != 2) {
        // mexErrMsgIdAndTxt("MyFFT:InvalidInput", "First input must be a real double matrix.");
    // }
    // if (!mxIsDouble(prhs[1]) || mxIsComplex(prhs[1]) || mxGetNumberOfDimensions(prhs[1]) != 2) {
        // mexErrMsgIdAndTxt("MyFFT:InvalidInput", "Second input must be a real double matrix.");
    // }
// 
    // size_t rowsA = mxGetM(prhs[0]);
    // size_t colsA = mxGetN(prhs[0]);
    // size_t rowsB = mxGetM(prhs[1]);
    // size_t colsB = mxGetN(prhs[1]);
// 
    // if (colsA != rowsB) {
        // mexErrMsgIdAndTxt("MyFFT:DimensionMismatch", "Inner matrix dimensions must agree.");
    // }
// 
    // plhs[0] = mxCreateDoubleMatrix(rowsA, colsB, mxREAL);
    // double *A = mxGetPr(prhs[0]);
    // double *B = mxGetPr(prhs[1]);
    // double *C = mxGetPr(plhs[0]);
// 
    // for (size_t i = 0; i < rowsA; i++) {
        // for (size_t j = 0; j < colsB; j++) {
            // C[i + j * rowsA] = 0;
            // for (size_t k = 0; k < colsA; k++) {
                // C[i + j * rowsA] += A[i + k * rowsA] * B[k + j * rowsB];
            // }
        // }
    // }
// }