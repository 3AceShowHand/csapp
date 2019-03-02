/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void trans_block(int M, int N, int A[N][M], int B[M][N]);

// void transpose_square(int size, int A[size][size], int B[size][size]);
// void transepose_rectangle(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    trans_block(M, N, A, B);
}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */

char trans_block_desc[] = "Transpose block";
void trans_block(int M, int N, int A[N][M], int B[M][N]) {
    int a, b, c, d, e, f, g, h;
    int i, j, k, t;
    if (N == 32) {
        for (i = 0; i < 32; i += 8) {
            for (j = 0; j < 32; j += 8) {
                for (k = i; k < i + 8; k++) {
                    a = A[k][j];
                    b = A[k][j + 1];
                    c = A[k][j + 2];
                    d = A[k][j + 3];
                    e = A[k][j + 4];
                    f = A[k][j + 5];
                    g = A[k][j + 6];
                    h = A[k][j + 7];

                    B[j][k] = a;
                    B[j + 1][k] = b;
                    B[j + 2][k] = c;
                    B[j + 3][k] = d;
                    B[j + 4][k] = e;
                    B[j + 5][k] = f;
                    B[j + 6][k] = g;
                    B[j + 7][k] = h;
                }
            }
        }
    } else if (N == 64) {
        for (i = 0; i < 64; i += 8) {
            for (j = 0; j < 64; j += 8) {
                for (k = j; k < j + 4; ++k) {
                    a = A[k][i];
                    b = A[k][i + 1];
                    c = A[k][i + 2];
                    d = A[k][i + 3];
                    e = A[k][i + 4];
                    f = A[k][i + 5];
                    g = A[k][i + 6];
                    h = A[k][i + 7];

                    B[i][k] = a;
                    B[i][k + 4] = e;
                    B[i + 1][k] = b;
                    B[i + 1][k + 4] = f;
                    B[i + 2][k] = c;
                    B[i + 2][k + 4] = g;
                    B[i + 3][k] = d;
                    B[i + 3][k + 4] = h;
                }
                for (k = i; k < i + 4; ++k) {
                    a = B[k][j + 4];
                    b = B[k][j + 5];
                    c = B[k][j + 6];
                    d = B[k][j + 7];
                    e = A[j + 4][k];
                    f = A[j + 5][k];
                    g = A[j + 6][k];
                    h = A[j + 7][k];

                    B[k][j + 4] = e;
                    B[k][j + 5] = f;
                    B[k][j + 6] = g;
                    B[k][j + 7] = h;
                    B[k + 4][j] = a;
                    B[k + 4][j + 1] = b;
                    B[k + 4][j + 2] = c;
                    B[k + 4][j + 3] = d;
                }
                for (k = i + 4; k < i + 8; ++k) {
                    a = A[j + 4][k];
                    b = A[j + 5][k];
                    c = A[j + 6][k];
                    d = A[j + 7][k];

                    B[k][j + 4] = a;
                    B[k][j + 5] = b;
                    B[k][j + 6] = c;
                    B[k][j + 7] = d;
                }
            }
        }
    } else {
        for (i = 0; i + 16 < N; i += 16) {
            for (j = 0; j + 16 < M; j += 16) {
                for (k = i; k < i + 16; k++) {
                    a = A[k][j];
                    b = A[k][j + 1];
                    c = A[k][j + 2];
                    d = A[k][j + 3];
                    e = A[k][j + 4];
                    f = A[k][j + 5];
                    g = A[k][j + 6];
                    h = A[k][j + 7];

                    B[j][k] = a;
                    B[j + 1][k] = b;
                    B[j + 2][k] = c;
                    B[j + 3][k] = d;
                    B[j + 4][k] = e;
                    B[j + 5][k] = f;
                    B[j + 6][k] = g;
                    B[j + 7][k] = h;

                    a = A[k][j + 8];
                    b = A[k][j + 9];
                    c = A[k][j + 10];
                    d = A[k][j + 11];
                    e = A[k][j + 12];
                    f = A[k][j + 13];
                    g = A[k][j + 14];
                    h = A[k][j + 15];

                    B[j + 8][k] = a;
                    B[j + 9][k] = b;
                    B[j + 10][k] = c;
                    B[j + 11][k] = d;
                    B[j + 12][k] = e;
                    B[j + 13][k] = f;
                    B[j + 14][k] = g;
                    B[j + 15][k] = h;
                }
            }
        }
        for (k = i; k < N; k++) {
            for (t = 0; t < M; t++) {
                B[t][k] = A[k][t];
            }
        }
        for (k = 0; k < i; k++) {
            for (t = j; t < M; t++) {
                B[t][k] = A[k][t];
            }
        }
    }
}

// void transpose_square(int size, int A[size][size], int B[size][size]) {
// }
// void transpose_rectangle(int M, int N, int A[N][M], int B[M][N]) {
// }

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc);
    // registerTransFunction(trans_block, trans_block_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
