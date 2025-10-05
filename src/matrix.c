#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    uint8_t rows;
    uint8_t cols;
} Matrix;

Matrix* create_matrix(uint8_t row_size, uint8_t col_size, uint8_t data) {
    Matrix *matrix = malloc(sizeof(Matrix));
    if (!matrix) return NULL;

    matrix -> rows = row_size;
    matrix -> cols = col_size;

    matrix -> data = malloc(row_size * col_size * sizeof(float));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    if (data) {
        for (int i = 0; i < rows * cols; i++) {
            matrix->data[i] = data[i];
        }
    }

    return matrix;
}

Matrix* matrix_multiplication(Matrix matrix_a, Matrix matrix_b) {

}
