#include "my_fft_cver.h"
#include "Complex.h"

#include <stdio.h>

int main(int argc, char** argv) {
    Complex source[4] = {
        newComplexDescartes(1.0, 0.0),
        newComplexDescartes(2.0, 0.0),
        newComplexDescartes(3.0, 0.0),
        newComplexDescartes(4.0, 0.0)
    };

    Complex* result = my_fft_cvar(source, 4, 2);

    printf("FFT Result:\n");
    for (int i = 0; i < 4; i++) {
        printf("result[%d] = %f + %fi\n", i, result[i].real, result[i].imag);
    }
    
    free(source);
    free(result);
}