#include "c_quaterniond.h"

#include <assert.h>
#include <math.h>

Quaternion* quaternion_copy(Quaternion* other){
    return matrix_copy(other);
}

Quaternion* quaternion_by_matrix(Matrix* data){
    assert(matrix_rows(data) == 3 && matrix_cols(data) == 3);
    Quaternion* q = vector_new(4); // x,y,z,w
    // 旋转矩阵转四元数
    DataType w = 0.5 * sqrt(1 + matrix_get_index(data, 0, 0) + matrix_get_index(data, 1, 1) + matrix_get_index(data, 2, 2));
    DataType x = (matrix_get_index(data, 2, 1) - matrix_get_index(data, 1, 2)) / (4 * w);
    DataType y = (matrix_get_index(data, 0, 2) - matrix_get_index(data, 2, 0)) / (4 * w);
    DataType z = (matrix_get_index(data, 1, 0) - matrix_get_index(data, 0, 1)) / (4 * w);

    return q;
}

Quaternion* quaternion_by_vector(Vector* data){
    assert(matrix_rows(data) == 3);
    Quaternion* q = vector_new(4); // x,y,z,w
    // 1e-6 防止除零
    if (vector_norm(data) < 1e-6) return vector_by_array((DataType[]){0, 0, 0, 1}, 4); 

    // 角轴转四元数
    DataType theta = vector_norm(data);
    DataType sin_theta = sin(theta / 2);
    DataType cos_theta = cos(theta / 2);
    vector_set_index(q, 0, sin_theta * vector_get_index(data, 0) / theta);
    vector_set_index(q, 1, sin_theta * vector_get_index(data, 1) / theta);
    vector_set_index(q, 2, sin_theta * vector_get_index(data, 2) / theta);
    vector_set_index(q, 3, cos_theta);
    return q;
}

Quaternion* quaternion_by_array(DataType* data){
    return vector_by_array(data, 4);
}

Quaternion* quaternion_by_value(DataType x, DataType y, DataType z, DataType w){
    return vector_by_array((DataType[]){x, y, z, w}, 4);
}

Quaternion* quaternion_normalize(Quaternion* data)
{
    DataType norm = quaternion_norm(data);
    return vector_mul_scalar(data, 1 / norm);
}

Matrix* quaternion_to_matrix(Quaternion* data)
{
    Matrix* m = matrix_new(3, 3);
    DataType x = vector_get_index(data, 0);
    DataType y = vector_get_index(data, 1);
    DataType z = vector_get_index(data, 2);
    DataType w = vector_get_index(data, 3);
    matrix_set_index(m, 0, 0, 1 - 2 * y * y - 2 * z * z);
    matrix_set_index(m, 0, 1, 2 * x * y - 2 * z * w);
    matrix_set_index(m, 0, 2, 2 * x * z + 2 * y * w);
    matrix_set_index(m, 1, 0, 2 * x * y + 2 * z * w);
    matrix_set_index(m, 1, 1, 1 - 2 * x * x - 2 * z * z);
    matrix_set_index(m, 1, 2, 2 * y * z - 2 * x * w);
    matrix_set_index(m, 2, 0, 2 * x * z - 2 * y * w);
    matrix_set_index(m, 2, 1, 2 * y * z + 2 * x * w);
    matrix_set_index(m, 2, 2, 1 - 2 * x * x - 2 * y * y);
    return m;
}

Vector* quaternion_to_vector(Quaternion* data)
{
    // 四元数转角轴
    DataType x = vector_get_index(data, 0);
    DataType y = vector_get_index(data, 1);
    DataType z = vector_get_index(data, 2);
    DataType w = vector_get_index(data, 3);
    DataType theta = 2 * acos(w);
    DataType sin_theta = sin(theta / 2);
    
    return vector_by_array((DataType[]){x * theta / sin_theta, y * theta / sin_theta, z * theta / sin_theta}, 3);
}

DataType quaternion_norm(Quaternion* data) { return vector_norm(data); }

Quaternion* quaternion_mul(Quaternion* data, Quaternion* other)
{
    Quaternion* q = vector_new(4);
    DataType x = vector_get_index(data, 0);
    DataType y = vector_get_index(data, 1);
    DataType z = vector_get_index(data, 2);
    DataType w = vector_get_index(data, 3);
    DataType x1 = vector_get_index(other, 0);
    DataType y1 = vector_get_index(other, 1);
    DataType z1 = vector_get_index(other, 2);
    DataType w1 = vector_get_index(other, 3);
    vector_set_index(q, 0, w * x1 + x * w1 + y * z1 - z * y1);
    vector_set_index(q, 1, w * y1 - x * z1 + y * w1 + z * x1);
    vector_set_index(q, 2, w * z1 + x * y1 - y * x1 + z * w1);
    vector_set_index(q, 3, w * w1 - x * x1 - y * y1 - z * z1);
    return q;
}

void quaternion_print(Quaternion* data) { vector_print(data); }
