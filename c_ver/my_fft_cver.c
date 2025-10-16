#include "Complex.h"

#define _USE_MATH_DEFINES
#include <mex.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int* bin_reverse(int fft_layer, int n) {
    int* reversed = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
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
        Complex W = newComplexPolar(1.0, (double) i * -2.0 * M_PI / N);
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
    int* bin_reversed_seq = bin_reverse(fft_layer, n);
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

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs > 2 || nrhs == 0) {
        mexErrMsgIdAndTxt("MyFFT:InvalidNumInputs", "One or two inputs required.");
    }
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("MyFFT:InvalidNumOutputs", "One output required.");
    }

    if ((!mxIsComplex(prhs[0]) && !mxIsDouble(prhs[0])) || mxGetNumberOfDimensions(prhs[0]) != 2) {
        mexErrMsgIdAndTxt("MyFFT:InvalidInput", "First input must be a complex double or real double matrix.");
    }

    size_t rowsA = mxGetM(prhs[0]);
    size_t colsA = mxGetN(prhs[0]);

    int N = 0;
    if (nrhs == 2) {
        if (!mxIsScalar(prhs[1])) {
            mexErrMsgIdAndTxt("MyFFT:InvalidInput", "Second input must be a scalar.");
        }
        N = (int) mxGetScalar(prhs[1]);
    } else {
        N = (int) rowsA;
    }

    if (colsA != 1) {
        mexErrMsgIdAndTxt("MyFFT:InvalidInpu", "Matrix A must be a column vector.");
    }

    size_t point_num = 0;
    if (N <= 0 || (N & (N - 1)) != 0) {
        point_num = (size_t) pow(2.0, ceil(log2((double) rowsA)));
    } else {
        point_num = (size_t) N;
    }

    Complex *source_code_complex = (Complex*)malloc((int) point_num * sizeof(Complex));

    if (!mxIsComplex(prhs[0])) {
        mxDouble *source_code = mxGetDoubles(prhs[0]);
        for (size_t i = 0; i < point_num; i++) {
            if (i < rowsA) {
                source_code_complex[i] = newComplexDescartes((double) source_code[i], 0.0);
            } else {
                source_code_complex[i] = newComplexDescartes(0.0, 0.0);
            }
        }
    } else {
        mxComplexDouble *source_code = mxGetComplexDoubles(prhs[0]);
        for (size_t i = 0; i < point_num; i++) {
            if (i < rowsA) {
                source_code_complex[i] = newComplexDescartes((double) source_code[i].real, (double) source_code[i].imag);
            } else {
                source_code_complex[i] = newComplexDescartes(0.0, 0.0);
            }
        }
    }

    int fft_layer = (int) log2((double) point_num);
    Complex* result = my_fft_cvar(source_code_complex, (int) point_num, fft_layer);

    plhs[0] = mxCreateDoubleMatrix(point_num, 1, mxCOMPLEX);
    mxComplexDouble *output = mxGetComplexDoubles(plhs[0]);

    for (size_t i = 0; i < point_num; i++) {
        output[i].real = result[i].real;
        output[i].imag = result[i].imag;
    }
}