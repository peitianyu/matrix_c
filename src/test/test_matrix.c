#include "common/c_test.h"
#include "common/logger.h"
#include "core/c_matrix.h"


// JUST_RUN_TEST(matrix, base)
TEST(matrix, base)
{
    LOG_TEST("*******************base*******************");
    Matrix* m = matrix_new(3, 4);
    LOG_TEST("*******************zero*******************");
    matrix_print(matrix_zero(3, 4));
    LOG_TEST("*******************ones*******************");
    matrix_print(matrix_ones(3, 4));
    LOG_TEST("*******************rand*******************");
    matrix_print(matrix_rand(3, 4));
    LOG_TEST("*******************copy*******************");
    matrix_print(matrix_copy(m));
    LOG_TEST("*******************rows*******************");
    LOG_TEST("%d", matrix_rows(m));
    LOG_TEST("*******************cols*******************");
    LOG_TEST("%d", matrix_cols(m));
    LOG_TEST("*******************size*******************");
    LOG_TEST("%d", matrix_size(m));
    LOG_TEST("*******************delete*****************");
    matrix_delete(m);
}

// JUST_RUN_TEST(matrix, set_get)
TEST(matrix, set_get)
{
    LOG_TEST("*******************set*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);
    LOG_TEST("*******************set_index*******************");
    matrix_set_index(m, 1, 1, 100);
    matrix_print(m);
    LOG_TEST("*******************set_row*******************");
    DataType data1[4] = {1, 2, 3, 4};
    matrix_set_row(m, 1, data1);
    matrix_print(m);
    LOG_TEST("*******************set_col*******************");
    DataType data2[3] = {1, 2, 3};
    matrix_set_col(m, 1, data2);
    matrix_print(m);
    LOG_TEST("*******************fill*******************");
    matrix_fill(m, 100);
    matrix_print(m);
    LOG_TEST("*******************get_index*******************");
    LOG_TEST("%f", matrix_get_index(m, 1, 1));
    LOG_TEST("*******************get_row*******************");
    matrix_print(matrix_get_row(m, 1));
    LOG_TEST("*******************get_col*******************");
    matrix_print(matrix_get_col(m, 1));
    matrix_delete(m);
}

// JUST_RUN_TEST(matrix, block)
TEST(matrix, block)
{
    LOG_TEST("*******************set_block*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);
    Matrix* m1 = matrix_new(2, 2);
    DataType data1[4] = {1, 2, 3, 4};
    matrix_set(m1, data1);
    matrix_print(m1);
    LOG_TEST("*******************set_block*******************");
    matrix_set_block(m, 1, 1, m1);
    matrix_print(m);
    LOG_TEST("*******************set_left*******************");
    matrix_set_left(m, 1, m1);
    matrix_print(m);
    LOG_TEST("*******************set_right*******************");
    matrix_set_right(m, 1, m1);
    matrix_print(m);
    LOG_TEST("*******************set_top*******************");
    matrix_set_top(m, 1, m1);
    matrix_print(m);
    LOG_TEST("*******************set_bottom*******************");
    matrix_set_bottom(m, 1, m1);
    matrix_print(m);

    LOG_TEST("*******************get_block*******************");
    matrix_print(matrix_get_block(m, 1, 1, 2, 2));
    LOG_TEST("*******************get_left*******************");
    matrix_print(matrix_get_left(m, 1, 2));
    LOG_TEST("*******************get_right*******************");
    matrix_print(matrix_get_right(m, 1, 2));
    LOG_TEST("*******************get_top*******************");
    matrix_print(matrix_get_top(m, 1, 2));
    LOG_TEST("*******************get_bottom*******************");
    matrix_print(matrix_get_bottom(m, 1, 2));

    matrix_delete(m);
}

// JUST_RUN_TEST(matrix, transpose)
TEST(matrix, transpose)
{
    LOG_TEST("*******************transpose*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);

    LOG_TEST("******************trans************************");
    matrix_print(matrix_trans(m));
    LOG_TEST("******************adjoint**********************");
    matrix_print(matrix_adjoint(m));
    LOG_TEST("******************diagonal*********************");
    matrix_print(matrix_diagonal(matrix_get_block(m, 1, 1, 2, 2)));
    LOG_TEST("******************conjugate********************");
    matrix_print(matrix_conjugate(m));

    matrix_delete(m);
}

// JUST_RUN_TEST(matrix, operation)
TEST(matrix, operation)
{
    LOG_TEST("*******************operation*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {-1, 2, 3, -4, 5, 6, 7, 8, 9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);

    Matrix* m1 = matrix_new(3, 4);
    DataType data1[12] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    matrix_set(m1, data1);
    matrix_print(m1);

    LOG_TEST("********************abs***********************");
    matrix_print(matrix_abs(m));
    LOG_TEST("********************add***********************");
    matrix_print(matrix_add(m, m1));
    LOG_TEST("********************sub***********************");
    matrix_print(matrix_sub(m, m1));
    LOG_TEST("********************mul***********************");
    matrix_print(matrix_mul(m, matrix_trans(m1)));
    LOG_TEST("********************div***********************");
    matrix_print(matrix_div(m, m1));
    LOG_TEST("********************mul_scalar***********************");
    matrix_print(matrix_mul_scalar(m, 0.1));

    matrix_delete(m);
    matrix_delete(m1);
}

// JUST_RUN_TEST(matrix, array)
TEST(matrix, array)
{
    LOG_TEST("*******************array*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);

    LOG_TEST("*******************add*******************");
    matrix_print(array_add(m, 2));
    LOG_TEST("*******************sub*******************");
    matrix_print(array_sub(m, 2));
    LOG_TEST("*******************mul*******************");
    matrix_print(array_mul(m, 2));
    LOG_TEST("*******************div*******************");
    matrix_print(array_div(m, 2));
    LOG_TEST("*******************pow*******************");
    matrix_print(array_pow(m, 2));
    LOG_TEST("*******************sqrt*******************");
    matrix_print(array_sqrt(m));
    LOG_TEST("*******************exp*******************");
    matrix_print(array_exp(m));
    LOG_TEST("*******************log*******************");
    matrix_print(array_log(m));
    LOG_TEST("*******************sum*******************");
    printf("%f\n", array_sum(m));
    LOG_TEST("*******************max*******************");
    printf("%f\n", array_max(m));
    LOG_TEST("*******************min*******************");
    printf("%f\n", array_min(m));

    matrix_delete(m);
}

// JUST_RUN_TEST(matrix, dot)
TEST(matrix, dot)
{
    LOG_TEST("*******************array*******************");
    Matrix* m = matrix_new(3, 4);
    DataType data[12] = {1, 2, 3, 4, 
                        5, 6, 7, 8, 
                        9 ,10 ,11 ,12};
    matrix_set(m, data);
    matrix_print(m);

    Matrix* m1 = matrix_new(3, 4);
    DataType data1[12] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    matrix_set(m1, data1);
    matrix_print(m1);

    LOG_TEST("*******************dot*******************");
    printf("%f\n", matrix_dot(matrix_get_left(m, 0, 1), matrix_get_left(m1, 0, 1)));
    LOG_TEST("*******************norm*******************");
    printf("%f\n", matrix_norm(matrix_get_left(m, 0, 1)));
    LOG_TEST("*******************det*******************");
    printf("%f\n", matrix_det(matrix_get_block(m, 0, 0, 2, 2)));
    LOG_TEST("*******************normalize*******************");
    matrix_print(matrix_normalize(matrix_get_left(m, 0, 1)));
    LOG_TEST("*******************inv*******************");
    matrix_print(matrix_inv(matrix_get_block(m, 0, 0, 2, 2)));
    LOG_TEST("*******************cross*******************");
    matrix_print(matrix_cross(matrix_get_block(m, 0, 0, 3, 1), matrix_get_block(m1, 0, 0, 3, 1)));
    
    matrix_delete(m);
    matrix_delete(m1);
}