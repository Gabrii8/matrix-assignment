public class MatrixTest {
    public static void main(String[] args) {

        double[][] A = { {1, 2}, {3, 4} };
        double[][] B = { {5, 6}, {7, 8} };
        double[][] C = MatrixOps.matmul(A, B);
        assert C[0][0] == 19 && C[0][1] == 22 && C[1][0] == 43 && C[1][1] == 50
            : "2x2 known product failed";

        double[][] I = { {1, 0}, {0, 1} };
        double[][] X = { {2, 3}, {4, 5} };
        double[][] XI = MatrixOps.matmul(X, I);
        assert XI[0][0] == 2 && XI[0][1] == 3 && XI[1][0] == 4 && XI[1][1] == 5
            : "Identity product failed";

        double[][] Z = { {0, 0}, {0, 0} };
        double[][] XZ = MatrixOps.matmul(X, Z);
        assert XZ[0][0] == 0 && XZ[0][1] == 0 && XZ[1][0] == 0 && XZ[1][1] == 0
            : "Zero product failed";

        System.out.println("All tests passed.");
    }
}
