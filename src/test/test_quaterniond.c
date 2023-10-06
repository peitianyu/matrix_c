#include "common/c_test.h"
#include "common/logger.h"
#include "core/c_quaterniond.h"


JUST_RUN_TEST(quaterniond, test)
TEST(quaterniond, test)
{
    Quaternion* q = quaternion_by_vector(vector_zero(3));
    quaternion_print(q);
    Quaternion* q_update = quaternion_by_vector(vector_by_array((DataType[]){0.01, 0.02, 0.03}, 3));
    quaternion_print(q_update);

    Quaternion* q_new = quaternion_mul(q, q_update);
    quaternion_print(q_new);
}