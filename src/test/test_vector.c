#include "common/c_test.h"
#include "common/logger.h"
#include "core/c_vector.h"


// JUST_RUN_TEST(vector, base)
TEST(vector, base)
{
    LOG_TEST("*******************base*******************");
    Vector* m = vector_new(3);
    vector_print(m);
    LOG_TEST("*******************zero*******************");
    vector_print((vector_zero(3)));
    LOG_TEST("*******************ones*******************");
    vector_print(vector_ones(3));
    LOG_TEST("*******************rand*******************");
    vector_print(vector_rand(3));
    LOG_TEST("*******************copy*******************");
    vector_print(vector_copy(m));
    LOG_TEST("*******************size*******************");
    LOG_TEST("%d", vector_size(m));
    LOG_TEST("*******************delete*****************");
    vector_delete(m);
}

// JUST_RUN_TEST(vector, set_get)
TEST(vector, set_get)
{
    LOG_TEST("*******************set*******************");
    Vector* m = vector_new(3);
    DataType data[3] = {1, 2, 3};
    vector_set(m, data);
    vector_print(m);
    LOG_TEST("*******************set_index*******************");
    vector_set_index(m, 1, 100);
    vector_print(m);
    LOG_TEST("*******************fill*******************");
    vector_fill(m, 100);
    vector_print(m);
    LOG_TEST("*******************get_index*******************");
    LOG_TEST("%f", vector_get_index(m, 1));

    vector_delete(m);
}

// JUST_RUN_TEST(vector, block)
TEST(vector, block)
{
    LOG_TEST("*******************set_block*******************");
    Vector* m = vector_new(3);
    DataType data[3] = {1, 2, 3};
    vector_set(m, data);
    vector_print(m);
    Vector* m1 = vector_new(2);
    DataType data1[2] = {3, 4};
    vector_set(m1, data1);
    vector_print(m1);
    vector_set_block(m, 1, m1);
    vector_print(m);
    LOG_TEST("*******************get_block*******************");
    vector_print(vector_get_block(m, 1, 2));
    vector_delete(m);
    vector_delete(m1);
}

// JUST_RUN_TEST(vector, operation)
TEST(vector, operation)
{
    LOG_TEST("*******************operation*******************");
    Vector* m = vector_by_array((float[3]){-1, 2, 3}, 3);
    vector_print(m);
    Vector* m1 = vector_by_array((float[3]){3, 4, 5}, 3);
    vector_print(m1);
    LOG_TEST("*******************abs*******************");
    vector_print(vector_abs(m));
    LOG_TEST("*******************add*******************");
    vector_print(vector_add(m, m1));
    LOG_TEST("*******************sub*******************");
    vector_print(vector_sub(m, m1));
    LOG_TEST("*******************mul*******************");
    Vector* m2 = vector_by_array((float[1]){3}, 1);
    vector_print(vector_mul(m, m2));
    LOG_TEST("*******************div*******************");
    vector_print(vector_div(m, m1));
    LOG_TEST("*******************mul_scalar*******************");
    vector_print(vector_mul_scalar(m, 2));
    vector_delete(m);
    vector_delete(m1);
    vector_delete(m2);
}

// JUST_RUN_TEST(vector, dot)
TEST(vector, dot)
{ 
    LOG_TEST("*******************dot*******************");
    Vector* m = vector_by_array((float[3]){1, 2, 3}, 3);
    vector_print(m);
    Vector* m1 = vector_by_array((float[3]){3, 4, 5}, 3);
    vector_print(m1);
    LOG_TEST("%f", vector_dot(m, m1));
    LOG_TEST("*******************norm*******************");
    LOG_TEST("%f", vector_norm(m));
    LOG_TEST("*******************normalize*******************");
    vector_print(vector_normalize(m));
    LOG_TEST("*******************cross*******************");
    vector_print(vector_cross(m, m1));
    vector_delete(m);
    vector_delete(m1);
}
