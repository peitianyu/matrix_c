#include "c_matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


Matrix* matrix_new(int row, int col)
{
    Matrix* cthis = (Matrix*)malloc(sizeof(Matrix));
    cthis->row = row;
    cthis->col = col;
    cthis->data = (DataType*)malloc(sizeof(DataType) * row * col);
    return cthis;
}

Matrix* matrix_zero(int row, int col)
{
    Matrix* cthis = matrix_new(row, col);
    memset(cthis->data, 0, sizeof(DataType) * row * col);
    return cthis;
}

Matrix* matrix_ones(int row, int col)
{
    Matrix* cthis = matrix_zero(row, col);
    for(int i = 0; i < row && i < col; i++)
        cthis->data[i * col + i] = 1;
    return cthis;
}

Matrix* matrix_rand(int row, int col)
{
    Matrix* cthis = matrix_new(row, col);
    for(int i = 0; i < row * col; i++)
        cthis->data[i] = rand() / (DataType)RAND_MAX;
    return cthis;
}

Matrix* matrix_copy(Matrix* other)
{
    Matrix* cthis = matrix_new(other->row, other->col);
    memcpy(cthis->data, other->data, sizeof(DataType) * cthis->row * cthis->col);
    return cthis;
}

void matrix_delete(Matrix* cthis)
{
    free(cthis->data);
    free(cthis);
}

int matrix_rows(Matrix* cthis)
{
    return cthis->row;
}

int matrix_cols(Matrix* cthis)
{
    return cthis->col;
}

int matrix_size(Matrix* cthis)
{
    return cthis->row * cthis->col;
}

void matrix_set(Matrix* cthis, DataType* value)
{
    memcpy(cthis->data, value, sizeof(DataType) * cthis->row * cthis->col);
}
void matrix_set_index(Matrix* cthis, int row, int col, DataType value)
{
    assert(row < cthis->row && col < cthis->col);
    cthis->data[row * cthis->col + col] = value;
}
void matrix_set_row(Matrix* cthis, int row, DataType* value)
{
    assert(row < cthis->row);
    memcpy(cthis->data + row * cthis->col, value, sizeof(DataType) * cthis->col);
}
void matrix_set_col(Matrix* cthis, int col, DataType* value)
{
    assert(col < cthis->col);
    for(int i = 0; i < cthis->row; i++)
        cthis->data[i * cthis->col + col] = value[i];
}
void matrix_fill(Matrix* cthis, DataType value)
{
    for(int i = 0; i < cthis->row * cthis->col; i++)
        cthis->data[i] = value;
}

DataType matrix_get_index(Matrix* cthis, int row, int col)
{
    assert(row < cthis->row && col < cthis->col);
    return cthis->data[row * cthis->col + col];
}

Matrix* matrix_get_row(Matrix* cthis, int row)
{
    assert(row < cthis->row);
    Matrix* result = matrix_new(1, cthis->col);
    memcpy(result->data, cthis->data + row * cthis->col, sizeof(DataType) * cthis->col);
    return result;
}

Matrix* matrix_get_col(Matrix* cthis, int col)
{
    assert(col < cthis->col);
    Matrix* result = matrix_new(cthis->row, 1);
    for(int i = 0; i < cthis->row; i++)
        result->data[i] = cthis->data[i * cthis->col + col];
    return result;
}

void matrix_set_block(Matrix* cthis, int row, int col, Matrix* block)
{
    assert(row + block->row <= cthis->row && col + block->col <= cthis->col);
    for(int i = 0; i < block->row; i++)
        for(int j = 0; j < block->col; j++)
            cthis->data[(row + i) * cthis->col + col + j] = block->data[i * block->col + j];
}
void matrix_set_left(Matrix* cthis, int col, Matrix* block)
{
    assert(col + block->col <= cthis->col);
    matrix_set_block(cthis, 0, col, block);
}

void matrix_set_right(Matrix* cthis, int col, Matrix* block)
{
    assert(col + block->col <= cthis->col);
    matrix_set_block(cthis, 0, cthis->col - col - block->col, block);
}

void matrix_set_top(Matrix* cthis, int row, Matrix* block)
{
    assert(row + block->row <= cthis->row);
    matrix_set_block(cthis, row, 0, block);
}

void matrix_set_bottom(Matrix* cthis, int row, Matrix* block)
{
    assert(row + block->row <= cthis->row);
    matrix_set_block(cthis, cthis->row - row - block->row, 0, block);
}

Matrix* matrix_get_block(Matrix* cthis, int row, int col, int row_size, int col_size)
{
    assert(row + row_size <= cthis->row && col + col_size <= cthis->col);
    Matrix* result = matrix_new(row_size, col_size);
    for(int i = 0; i < row_size; i++)
        for(int j = 0; j < col_size; j++)
            result->data[i * col_size + j] = cthis->data[(row + i) * cthis->col + col + j];
    return result;
}

Matrix* matrix_get_left(Matrix* cthis, int col, int row_size)
{
    assert(col + row_size <= cthis->col);
    return matrix_get_block(cthis, 0, col, cthis->row, row_size);
}

Matrix* matrix_get_right(Matrix* cthis, int col, int row_size)
{
    assert(col + row_size <= cthis->col);
    return matrix_get_block(cthis, 0, cthis->col - col - row_size, cthis->row, row_size);
}

Matrix* matrix_get_top(Matrix* cthis, int row, int col_size)
{
    assert(row + col_size <= cthis->row);
    return matrix_get_block(cthis, row, 0, col_size, cthis->col);
}

Matrix* matrix_get_bottom(Matrix* cthis, int row, int col_size)
{
    assert(row + col_size <= cthis->row);
    return matrix_get_block(cthis, cthis->row - row - col_size, 0, col_size, cthis->col);
}

Matrix* matrix_trans(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->col, cthis->row);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[j * cthis->row + i] = cthis->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_adjoint(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->col, cthis->row);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[j * cthis->row + i] = cthis->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_diagonal(Matrix* cthis)
{
    assert(cthis->row == cthis->col);
    Matrix* result = matrix_new(cthis->row, 1);
    for(int i = 0; i < cthis->row; i++)
        result->data[i] = cthis->data[i * cthis->col + i];
    return result;
}

Matrix* matrix_conjugate(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[i * cthis->col + j] = cthis->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_abs(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = (cthis->data[i] > 0 ? cthis->data[i] : -cthis->data[i]);
    return result;
}

Matrix* matrix_add(Matrix* cthis, Matrix* other)
{
    assert(cthis->row == other->row && cthis->col == other->col);
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[i * cthis->col + j] = cthis->data[i * cthis->col + j] + other->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_sub(Matrix* cthis, Matrix* other)
{
    assert(cthis->row == other->row && cthis->col == other->col);
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[i * cthis->col + j] = cthis->data[i * cthis->col + j] - other->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_mul(Matrix* cthis, Matrix* other)
{
    assert(cthis->col == other->row);
    Matrix* result = matrix_new(cthis->row, other->col);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < other->col; j++)
            for(int k = 0; k < cthis->col; k++)
                result->data[i * other->col + j] += cthis->data[i * cthis->col + k] * other->data[k * other->col + j];
    return result;
}

Matrix* matrix_div(Matrix* cthis, Matrix* other)
{
    assert(cthis->row == other->row && cthis->col == other->col);
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++)
            result->data[i * cthis->col + j] = cthis->data[i * cthis->col + j] / other->data[i * cthis->col + j];
    return result;
}

Matrix* matrix_mul_scalar(Matrix* cthis, DataType scalar)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = cthis->data[i] * scalar;
    return result;
}

Matrix* array_add(Matrix* cthis, DataType scalar)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = cthis->data[i] + scalar;
    return result;
}

Matrix* array_sub(Matrix* cthis, DataType scalar)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = cthis->data[i] - scalar;
    return result;
}

Matrix* array_mul(Matrix* cthis, DataType scalar)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = cthis->data[i] * scalar;
    return result;
}

Matrix* array_div(Matrix* cthis, DataType scalar)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = cthis->data[i] / scalar;
    return result;
}

Matrix* array_pow(Matrix* cthis, int n)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = pow(cthis->data[i], n);
    return result;
}

Matrix* array_sqrt(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = sqrt(cthis->data[i]);
    return result;
}

Matrix* array_exp(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = exp(cthis->data[i]);
    return result;
}

Matrix* array_log(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result->data[i] = log(cthis->data[i]);
    return result;
}

DataType array_sum(Matrix* cthis)
{
    DataType result = 0;
    for(int i = 0; i < cthis->row * cthis->col; i++)
        result += cthis->data[i];
    return result;
}

DataType array_max(Matrix* cthis)
{
    DataType result = cthis->data[0];
    for(int i = 1; i < cthis->row * cthis->col; i++)
        if(cthis->data[i] > result) result = cthis->data[i];
    return result;
}

DataType array_min(Matrix* cthis)
{
    DataType result = cthis->data[0];
    for(int i = 1; i < cthis->row * cthis->col; i++)
        if(cthis->data[i] < result) result = cthis->data[i];
    return result;
}

DataType matrix_dot(Matrix* cthis, Matrix* other)
{
    assert(cthis->row == other->row && cthis->col == other->col && cthis->col == 1);
    DataType result = 0;
    for(int i = 0; i < cthis->row; i++)
        result += cthis->data[i] * other->data[i];
    return result;
}

DataType matrix_norm(Matrix* cthis)
{
    assert(cthis->col == 1);
    DataType result = 0;
    for(int i = 0; i < cthis->row; i++)
        result += cthis->data[i] * cthis->data[i];
    return sqrt(result);
}

DataType matrix_det(Matrix* cthis)
{
    assert(cthis->row == cthis->col);
    DataType result = 0;
    if(cthis->row == 1) return cthis->data[0];
    if(cthis->row == 2) return cthis->data[0] * cthis->data[3] - cthis->data[1] * cthis->data[2];
    for(int i = 0; i < cthis->row; i++){
        Matrix* sub = matrix_get_block(cthis, 1, 0, cthis->row - 1, i);
        result += pow(-1, i) * cthis->data[i] * matrix_det(sub);
        matrix_delete(sub);
    } 
    return result;
}

Matrix* matrix_normalize(Matrix* cthis)
{
    Matrix* result = matrix_new(cthis->row, cthis->col);
    DataType norm = matrix_norm(cthis);
    for(int i = 0; i < cthis->row; i++)
        result->data[i] = cthis->data[i] / norm;
    return result;
}

Matrix* matrix_inv(Matrix* cthis)
{
    assert(cthis->row == cthis->col);
    Matrix* result = matrix_new(cthis->row, cthis->col);
    DataType det = matrix_det(cthis);
    if(det == 0) return result;
    if(cthis->row == 1){
        result->data[0] = 1 / cthis->data[0];
        return result;
    }
    if(cthis->row == 2){
        result->data[0] = cthis->data[3] / det;
        result->data[1] = -cthis->data[1] / det;
        result->data[2] = -cthis->data[2] / det;
        result->data[3] = cthis->data[0] / det;
        return result;
    }
    for(int i = 0; i < cthis->row; i++)
        for(int j = 0; j < cthis->col; j++){
            Matrix* sub = matrix_get_block(cthis, i, j, cthis->row - 1, cthis->col - 1);
            result->data[j * cthis->row + i] = pow(-1, i + j) * matrix_det(sub) / det;
            matrix_delete(sub);
        }
    return result;
}

Matrix* matrix_cross(Matrix* cthis, Matrix* other)
{
    // // 实现三维向量的叉乘
    assert(cthis->row == 3 && other->row == 3 && cthis->col == 1 && other->col == 1);
    Matrix* result = matrix_new(3, 1);
    result->data[0] = cthis->data[1] * other->data[2] - cthis->data[2] * other->data[1];
    result->data[1] = cthis->data[2] * other->data[0] - cthis->data[0] * other->data[2];
    result->data[2] = cthis->data[0] * other->data[1] - cthis->data[1] * other->data[0];
    return result;
}

DataType normalize_angle(DataType angle)
{
    while(angle > M_PI) angle -= 2 * M_PI;
    while(angle < -M_PI) angle += 2 * M_PI;
    return angle;
}

Matrix* angle2rot2d(DataType angle)
{
    Matrix* result = matrix_new(2, 2);
    matrix_set(result, (DataType[4]){cos(angle), -sin(angle), 
                                     sin(angle), cos(angle)});
    return result;
}

void matrix_print(Matrix* cthis)
{
    for(int i = 0; i < cthis->row; i++){
        for(int j = 0; j < cthis->col; j++)
            printf("%f ", cthis->data[i * cthis->col + j]);
        printf("\n");
    }
}


