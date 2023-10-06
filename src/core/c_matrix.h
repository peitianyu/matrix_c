#ifndef __MATRIX_H__
#define __MATRIX_H__


#include <stdio.h>

#define M_PI (3.14159265358979323846) // pi

typedef unsigned char uint8_t;
typedef float DataType;

typedef struct Matrix {
    int row, col;
    DataType* data;
} Matrix;

/////////////////base////////////////////
Matrix* matrix_new(int row, int col);
Matrix* matrix_zero(int row, int col);
Matrix* matrix_ones(int row, int col);
Matrix* matrix_rand(int row, int col);
Matrix* matrix_copy(Matrix* other);
int matrix_rows(Matrix* cthis);
int matrix_cols(Matrix* cthis);
int matrix_size(Matrix* cthis);
void matrix_delete(Matrix* cthis);

/////////////////set_get////////////////////
void matrix_set(Matrix* cthis, DataType* value);
void matrix_set_index(Matrix* cthis, int row, int col, DataType value);
void matrix_set_row(Matrix* cthis, int row, DataType* value);
void matrix_set_col(Matrix* cthis, int col, DataType* value);
void matrix_fill(Matrix* cthis, DataType value);
DataType matrix_get_index(Matrix* cthis, int row, int col);
Matrix* matrix_get_row(Matrix* cthis, int row);
Matrix* matrix_get_col(Matrix* cthis, int col);

/////////////////block////////////////////
void matrix_set_block(Matrix* cthis, int row, int col, Matrix* block);
void matrix_set_left(Matrix* cthis, int col, Matrix* block);
void matrix_set_right(Matrix* cthis, int col, Matrix* block);
void matrix_set_top(Matrix* cthis, int row, Matrix* block);
void matrix_set_bottom(Matrix* cthis, int row, Matrix* block);

Matrix* matrix_get_block(Matrix* cthis, int row, int col, int row_size, int col_size);
Matrix* matrix_get_left(Matrix* cthis, int col, int row_size);
Matrix* matrix_get_right(Matrix* cthis, int col, int row_size);
Matrix* matrix_get_top(Matrix* cthis, int row, int col_size);
Matrix* matrix_get_bottom(Matrix* cthis, int row, int col_size);

//////////////////transpose//////////////
Matrix* matrix_trans(Matrix* cthis);
Matrix* matrix_adjoint(Matrix* cthis);
Matrix* matrix_diagonal(Matrix* cthis);
Matrix* matrix_conjugate(Matrix* cthis);

//////////////////operation//////////////
Matrix* matrix_abs(Matrix* cthis);
Matrix* matrix_add(Matrix* cthis, Matrix* other);
Matrix* matrix_sub(Matrix* cthis, Matrix* other);
Matrix* matrix_mul(Matrix* cthis, Matrix* other);
Matrix* matrix_div(Matrix* cthis, Matrix* other);
Matrix* matrix_mul_scalar(Matrix* cthis, DataType scalar);

/////////////////array///////////////////
Matrix* array_add(Matrix* cthis, DataType scalar);
Matrix* array_sub(Matrix* cthis, DataType scalar);
Matrix* array_mul(Matrix* cthis, DataType scalar);
Matrix* array_div(Matrix* cthis, DataType scalar);
Matrix* array_pow(Matrix* cthis, int n);
Matrix* array_sqrt(Matrix* cthis);
Matrix* array_exp(Matrix* cthis);
Matrix* array_log(Matrix* cthis);
DataType array_sum(Matrix* cthis);
DataType array_max(Matrix* cthis);
DataType array_min(Matrix* cthis);

/////////////////dot/////////////////////
DataType matrix_dot(Matrix* cthis, Matrix* other);
DataType matrix_norm(Matrix* cthis);
DataType matrix_det(Matrix* cthis);
Matrix* matrix_normalize(Matrix* cthis);
Matrix* matrix_inv(Matrix* cthis);
Matrix* matrix_cross(Matrix* cthis, Matrix* other);

/////////////////geometry////////////////
DataType normalize_angle(DataType angle);
Matrix* angle2rot2d(DataType angle);

////////////////print///////////////////
void matrix_print(Matrix* cthis);


#endif // MATRIX_H