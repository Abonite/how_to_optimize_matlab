#ifndef __COMPLEX_H__
    #define __COMPLEX_H__

    typedef struct {
        double real;
        double imag;
    } Complex;

    Complex newComplexDescartes(double real, double imag);
    Complex newComplexPolar(double magnitude, double angle);

    Complex addComplex(Complex a, Complex b);
    Complex subComplex(Complex a, Complex b);
    Complex mulComplex(Complex a, Complex b);
    Complex divComplex(Complex a, Complex b);
#endif