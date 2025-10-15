import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Locale;
import java.util.Random;

public class MatrixCLI {

    private static double[][] randomMatrix(int n, long seed) {
        Random rng = new Random(seed);
        double[][] M = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = rng.nextDouble();
        return M;
    }

    private static void appendCsv(String path, int n, int reps, double avgSeconds) throws IOException {
        Path p = Paths.get(path);
        if (p.getParent() != null) Files.createDirectories(p.getParent());
        boolean exists = Files.exists(p);
        try (BufferedWriter w = Files.newBufferedWriter(
                p,
                java.nio.charset.StandardCharsets.UTF_8,
                StandardOpenOption.CREATE,
                StandardOpenOption.APPEND)) {
            if (!exists) w.write("MatrixSize,Repeats,AverageTime(s)\n");
            w.write(n + "," + reps + "," + String.format(Locale.US, "%.6f", avgSeconds) + "\n");
        }
    }

    public static void main(String[] args) throws Exception {
        int n = 128;
        int repeats = 3;
        String csvPath = "output-data/results_java.csv";
        long seedA = 42L, seedB = 43L;

        for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "--size":
                    if (i + 1 < args.length) n = Integer.parseInt(args[++i]);
                    break;
                case "--repeats":
                    if (i + 1 < args.length) repeats = Integer.parseInt(args[++i]);
                    break;
                case "--csv":
                    if (i + 1 < args.length) csvPath = args[++i];
                    break;
                default:
            }
        }

        System.out.printf("%n[Running %d repetitions with %dx%d matrices]%n%n", repeats, n, n);

        double sum = 0.0;
        for (int r = 1; r <= repeats; r++) {
            double[][] A = randomMatrix(n, seedA + r);
            double[][] B = randomMatrix(n, seedB + r);

            long t0 = System.nanoTime();
            double[][] C = MatrixOps.matmul(A, B); 
            long t1 = System.nanoTime();

            double seconds = (t1 - t0) / 1e9;
            sum += seconds;
            System.out.printf("Run %d: %.6f seconds%n", r, seconds);
        }

        double avg = sum / repeats;
        System.out.printf("%nAverage time (%d runs): %.6f seconds%n%n", repeats, avg);

        appendCsv(csvPath, n, repeats, avg);
        System.out.println("[Results saved to " + csvPath + "]");
    }
}
