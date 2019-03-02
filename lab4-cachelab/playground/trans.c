#include <stdio.h>
#include <stdlib.h>

void trans_block(int row, int col, int A[row][col], int B[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j) {
                continue;
            }
            int tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}


int main() {
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0 ,0}};
    trans_block(3, 3, a, b);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    return 0;

}
