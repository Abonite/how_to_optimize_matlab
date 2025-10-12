import java.lang.Math;
import java.util.ArrayList;
import java.util.Arrays;

public class my_fft_javaver {
    Complex[] before_fft_vector;
    int fft_layer;
    int N;

    double log2 = Math.log(2);

    my_fft_javaver(Complex[] source_codes) {
        this.fft_layer = (int) Math.ceil(this.log2(source_codes.length));
        this.N = (int) Math.pow(2.0, (double) this.fft_layer);
        Complex[] zeros = new Complex[this.N - source_codes.length];
        Arrays.fill(zeros, new Complex(0.0, 0.0));
        
        ArrayList temp_bfv = new ArrayList<Complex>(Arrays.asList(source_codes));
        temp_bfv.addAll(Arrays.asList(zeros));
        this.before_fft_vector = temp_bfv.toArray();
    }

    my_fft_javaver(Complex[] source_codes, int fft_pointer) {
        if (fft_pointer < source_codes.length) {
            System.out.println("Error: the second parameter should be 1");
            return;
        }
        this.N = fft_pointer;
        double temp_fft_layer = this.log2((double) fft_pointer);
        if (temp_fft_layer != (int) temp_fft_layer) {
            System.out.println("Error: the second parameter should be 2^n");
            return;
        } else {
            this.fft_layer = (int) temp_fft_layer;
        }

        Complex[] zeros = new Complex[this.N - source_codes.length];
        ArrayList temp_bfv = new ArrayList<Complex>(Arrays.asList(source_codes));
        temp_bfv.addAll(Arrays.asList(zeros));
        this.before_fft_vector = (Complex[]) temp_bfv.toArray();
    }

    public Complex[] do_fft() {
        Complex[] middle_vectory = new Complex[this.before_fft_vector.length];
        int[] index_bin_rev_seq = this.bit_reverse();
        for (int i = 0; i < this.before_fft_vector.length; i++) {
            middle_vectory[i] = this.before_fft_vector[index_bin_rev_seq[i]];
        }

        for (int i = 0; i < this.fft_layer; i++) {
            int gap = (int) Math.pow(2.0, (double) i);
            int sub_l = (int) Math.pow(2.0, (double) (i + 1));
            for (int j = 0; j < N; j += gap) {
                Complex[] temp = this.subo(Arrays.copyOfRange(middle_vectory, j, j + sub_l), gap);
                for (int k = 0; k < gap; k++) {
                    middle_vectory[j + k] = temp[k];
                }
            }
        }

        return middle_vectory;
    }

    private double log2(double n) {
        return Math.log(n) / this.log2;
    }

    private int[] bit_reverse() {
        int[] index_bin_rev_seq = new int[this.fft_layer];
        for (int i = 0; i < Math.pow(2.0, (double) this.fft_layer); i++) {
            int temp = 0;
            for (int j = 0; j < this.fft_layer; j++) {
                temp |= ((i >> j) & 1) << (this.fft_layer - 1 - j);
            }
            index_bin_rev_seq[i] = temp;
        }

        return index_bin_rev_seq;
    }

    private Complex[] subo(Complex[] source_pints, int gap) {
        int loop_t = source_pints.length / 2;
        Complex[] result = new Complex[source_pints.length];
        int N = 2 * gap;
        for (int i = 0; i < loop_t; i++) {
            Complex W = new Complex(N, -i * 2 * Math.PI / N, false);
            butterfly btfl = new butterfly(W);
            Complex i_a = source_pints[i];
            Complex i_b = source_pints[i + gap];
            Complex[] out = btfl.operate(i_a, i_b);
            result[i] = out[0];
            result[i + gap] = out[1];
        }
        return result;
    }
}
