#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "matmul.h"

#if defined(_WIN32)
  #include <direct.h>
  #define MKDIR(p) _mkdir(p)
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #define MKDIR(p) mkdir((p), 0777)
#endif

static void ensure_dir(const char *path) {
    MKDIR(path);
}

static double now_seconds(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + 1e-6 * (double)t.tv_usec;
}

int main(int argc, char **argv) {
    int n = 128;
    int reps = 3;
    const char *csv_path = "output-data/results_c.csv";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--size") == 0 && i + 1 < argc) {
            n = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--repeats") == 0 && i + 1 < argc) {
            reps = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--csv") == 0 && i + 1 < argc) {
            csv_path = argv[++i];
        }
    }

    printf("\n[Running %d repetitions with %dx%d matrices]\n\n", reps, n, n);

    size_t bytes = (size_t)n * (size_t)n * sizeof(double);
    double *A = (double*) malloc(bytes);
    double *B = (double*) malloc(bytes);
    double *C = (double*) malloc(bytes);
    if (!A || !B || !C) {
        fprintf(stderr, "Allocation failed\n");
        free(A); free(B); free(C);
        return 1;
    }

    ensure_dir("output-data");
    int need_header = 0;
    FILE *check = fopen(csv_path, "r");
    if (!check) need_header = 1; else fclose(check);

    FILE *csv = fopen(csv_path, "a");
    if (!csv) {
        perror("fopen");
        free(A); free(B); free(C);
        return 1;
    }
    if (need_header) fprintf(csv, "MatrixSize,Repeats,AverageTime(s)\n");

    // Benchmark
    double total = 0.0;
    for (int r = 1; r <= reps; ++r) {
        for (int i = 0; i < n*n; ++i) A[i] = (double) rand() / RAND_MAX;
        for (int i = 0; i < n*n; ++i) B[i] = (double) rand() / RAND_MAX;

        double t0 = now_seconds();
        matmul_ijk(A, B, C, n);
        double t1 = now_seconds();

        double secs = t1 - t0;
        total += secs;
        printf("Run %d: %.6f seconds\n", r, secs);
    }

    double avg = total / (double)reps;
    printf("\nAverage time (%d runs): %.6f seconds\n\n", reps, avg);

    fprintf(csv, "%d,%d,%.6f\n", n, reps, avg);
    fclose(csv);

    free(A); free(B); free(C);

    printf("[Results saved to %s]\n", csv_path);
    return 0;
}
