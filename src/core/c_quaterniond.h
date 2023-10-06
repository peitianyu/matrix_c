#ifndef __CORE_C_QUATERNIOND_H__
#define __CORE_C_QUATERNIOND_H__

#include "c_vector.h"
#include "c_matrix.h"

////////////////////Quaternion//////////////////////
typedef Vector Quaternion;


////////////////////base///////////////////////////
Quaternion* quaternion_copy(Quaternion* other);
Quaternion* quaternion_by_matrix(Matrix* data); // 3x3
Quaternion* quaternion_by_vector(Vector* data); // x,y,z
Quaternion* quaternion_by_array(DataType* data); // x,y,z,w
Quaternion* quaternion_by_value(DataType x, DataType y, DataType z, DataType w);
Quaternion* quaternion_normalize(Quaternion* data);

Matrix* quaternion_to_matrix(Quaternion* data);
Vector* quaternion_to_vector(Quaternion* data);

DataType quaternion_norm(Quaternion* data);

////////////////////operation///////////////////////////
Quaternion* quaternion_mul(Quaternion* data, Quaternion* other);


////////////////////print///////////////////////////
void quaternion_print(Quaternion* data);


#endif // __CORE_C_QUATERNIOND_H__