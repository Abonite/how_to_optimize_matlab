import java.lang.Math;

public class Complex {
    double real;
    double imag;

    Complex(double real, double imag) {
        this.real = real;
        this.imag = imag;
    }

    /**
     * @param a is module or real
     * @param b is radian or imag
     * @param ccs tells java how to resolution the parameters
     */
    public Complex(double a, double b, boolean ccs) {
        if (ccs) {
            this.real = a;
            this.imag = b;
        } else {
            this.real = a * Math.cos(b);
            this.imag = a * Math.sin(b);
        }
    }

    public void SetInCCS(double real, double imag) {
        this.real = real;
        this.imag = imag;
    }

    public void SetInPCS(double mod, double angle) {
        this.real = mod * Math.cos(angle);
        this.imag = mod * Math.sin(angle);
    }

    public void Add(Complex b) {
        this.real += b.real;
        this.imag += b.imag;
    }

    public void Min(Complex b) {
        this.real -= b.real;
        this.imag -= b.imag;
    }

    //  (a + bi)(c + di)
    // =(ac - bd) + (ad + bc)i
    public void Mul(Complex b) {
        double real = (this.real * b.real) - (this.imag * b.imag);
        double imag = (this.real * b.imag) + (this.imag * b.real);
        this.real = real;
        this.imag = imag;
    }

    //  (a + bi) / (c + di)
    // =(a + bi)(c - di) / (c + di)(c - di)
    // =((ac + bd) + (bc - ad)i) / (c^2 + d^2)
    // =((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2))i
    public void Div(Complex b) {
        double denom = (b.real * b.real) + (b.imag * b.imag);
        double numer_real = (this.real * b.real) + (this.imag * b.imag);
        double numer_imag = (this.imag * b.real) - (this.real * b.imag);
        this.real = numer_real / denom;
        this.imag = numer_imag / denom;
    }

    public void IntegerPow(int times) {
        if (times == 0) {
            this.real = 1;
            this.imag = 0;
        } else {
            Complex q = new Complex(this.real, this.imag);
            for (int i = 0; i < times; i++) {
                this.Mul(q);
            }
        }
    }

    @Override
    public String toString() {
        return "Complex[real = " + this.real + ", imag = " + this.imag + "]";       
    }

    public double getReal() {
        return this.real;
    }

    public double getImag() {
        return this.imag;
    }
}