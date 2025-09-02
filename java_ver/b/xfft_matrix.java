import java.util.ArrayList;
import java.lang.Math;

public class xfft_matrix {
    ArrayList<ArrayList<Complex>> matrix = new ArrayList<>();

    xfft_matrix(int n, boolean type) {
        Complex omega = new Complex(1.0, 2 * Math.PI / n, false);
        if (type) {
            omega.SetInPCS(1.0, 2 * Math.PI / n);
        } else {
            omega.SetInPCS(1.0, -2 * Math.PI / n);
        }

        for (int i = 0; i < n; i++) {
            var col = new ArrayList<Complex>();
            for (int j = 0; j < n; j++) {
                Complex somega = new Complex(omega.real, omega.imag);
                somega.IntegerPow(i * j);
                col.add(somega);
            }
            this.matrix.add(col);
        }
    }

    public ArrayList<ArrayList<Complex>> GetFullMatrix() {
        return this.matrix;
    }

    // 打印
    public void print() {
        var m = this.matrix;
        for (int i = 0; i < m.size(); i++) {
            StringBuilder sb = new StringBuilder();
            var col = m.get(i);
            sb.append("[");
            for (int j = 0; j < col.size(); j++) {
                sb.append(col.get(j).toString()).append(", ");
            }
            sb.append("]");
            System.out.println(sb.toString());
        }
    }
}
