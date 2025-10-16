#include "complex.h"

int* bin_reverse(int fft_layer);
Complex* butterfly(Complex i1, Complex i2, Complex W);
Complex* subo(Complex* source_points, int source_points_length, int gap);
Complex* my_fft_cvar(Complex* input, int n, int fft_layer);