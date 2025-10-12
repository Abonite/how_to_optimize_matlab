public class test {
    public static void main(String[] args) {
        Complex[] source_codes = new Complex[]{new Complex(1.0, 0.0), new Complex(2.0, 0.0), new Complex(3.0, 0.0), new Complex(4.0, 0.0)};
        my_fft_javaver test_fft = new my_fft_javaver(source_codes);

        Complex[] result = test_fft.do_fft();
        for (int i = 0; i < result.length; i++) {
            System.out.println(result[i]);
        }
    }
}
