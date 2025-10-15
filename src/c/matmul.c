#include "matmul.h"

#define IDX(i,j,n) ((i)*(n) + (j))

void matmul_ijk(const double *A, const double *B, double *C, int n) {
    // Mismo estilo que el base: i -> j -> k y acumulación con +=
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) {
                sum += A[IDX(i,k,n)] * B[IDX(k,j,n)];
            }
            C[IDX(i,j,n)] = sum;
        }
    }
}
