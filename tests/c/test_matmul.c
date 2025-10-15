#include <stdio.h>
#include <assert.h>
#include "matmul.h"

#define IDX(i,j,n) ((i)*(n) + (j))

int main() {
    int n = 2;

    double A[4] = {1, 2,
                   3, 4};
    double B[4] = {5, 6,
                   7, 8};
    double C[4];

    matmul_ijk(A, B, C, n);

    assert(C[IDX(0,0,n)] == 19);
    assert(C[IDX(0,1,n)] == 22);
    assert(C[IDX(1,0,n)] == 43);
    assert(C[IDX(1,1,n)] == 50);

    printf("All C matrix multiplication tests passed.\n");
    return 0;
}
