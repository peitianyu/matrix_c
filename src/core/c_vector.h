#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "c_matrix.h"

////////////////vector///////////////////
typedef Matrix Vector;

/////////////////base////////////////////
Vector* vector_new(int size);
Vector* vector_zero(int size);
Vector* vector_ones(int size);
Vector* vector_rand(int size);
Vector* vector_copy(Vector* other);
Vector* vector_by_array(DataType* data, int size);
int vector_size(Vector* cthis);
void vector_delete(Vector* cthis);

/////////////////set_get///////////////////
void vector_set(Vector* cthis, DataType* value);
void vector_set_index(Vector* cthis, int index, DataType value);
void vector_fill(Vector* cthis, DataType value);
DataType vector_get_index(Vector* cthis, int index);

/////////////////block//////////////////////
void vector_set_block(Vector* cthis, int index, Vector* block);
Vector* vector_get_block(Vector* cthis, int index, int size);

//////////////////transpose//////////////////
Vector* vector_trans(Vector* cthis);

//////////////////operation//////////////
Vector* vector_abs(Vector* cthis);
Vector* vector_add(Vector* cthis, Vector* other);
Vector* vector_sub(Vector* cthis, Vector* other);
Vector* vector_mul(Vector* cthis, Vector* other);
Vector* vector_div(Vector* cthis, Vector* other);
Vector* vector_mul_scalar(Vector* cthis, DataType scalar);

//////////////////dot////////////////////////
DataType vector_dot(Vector* cthis, Vector* other);
DataType vector_norm(Vector* cthis);
Vector* vector_normalize(Vector* cthis);
Vector* vector_cross(Vector* cthis, Vector* other);

/////////////////geometry///////////////////


////////////////print///////////////////
void vector_print(Vector* cthis);

#endif // __VECTOR_H__