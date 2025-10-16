#include "my_fft_cver.h"
#include "Complex.h"

int main(int argc, char** argv) {
    Complex source[4] = {
        newComplexDescartes(1.0, 0.0),
        newComplexDescartes(2.0, 0.0),
        newComplexDescartes(3.0, 0.0),
        newComplexDescartes(4.0, 0.0)
    };

    Complex* result = my_fft_cvar(source, 2, 4);

    free(source);
    free(result);
}