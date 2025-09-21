public class butterfly {
    Complex W;

    butterfly(Complex W) {
        this.W = W;
    }

    Complex[] operate(Complex i1, Complex i2) {
        Complex[] result = new Complex[2];
        this.W.Mul(i2);

        result[0] = i1;
        result[1] = i1;
        result[1].Add(i2);
        result[0].Min(i2);
        return result;
    }
}
