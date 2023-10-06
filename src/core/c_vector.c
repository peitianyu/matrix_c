#include "c_vector.h"

Vector* vector_new(int size) { return matrix_new(size, 1); }
Vector* vector_zero(int size) { return matrix_zero(size, 1); }
Vector* vector_ones(int size) { return matrix_ones(size, 1); }
Vector* vector_rand(int size) { return matrix_rand(size, 1); }
Vector* vector_copy(Vector* other) { return matrix_copy(other); }
Vector* vector_by_array(DataType* data, int size) 
{
    Vector* cthis = vector_new(size);
    for (int i = 0; i < size; i++)
        vector_set_index(cthis, i, data[i]);
    return cthis;
}
int vector_size(Vector* cthis) { return matrix_rows(cthis); }
void vector_delete(Vector* cthis) { matrix_delete(cthis); }

/////////////////set_get////////////////////
void vector_set(Vector* cthis, DataType* value) { matrix_set(cthis, value); }
void vector_set_index(Vector* cthis, int index, DataType value) { matrix_set_index(cthis, index, 0, value); }
void vector_fill(Vector* cthis, DataType value) { matrix_fill(cthis, value); }
DataType vector_get_index(Vector* cthis, int index) { return matrix_get_index(cthis, index, 0); }

/////////////////block////////////////////
void vector_set_block(Vector* cthis, int index, Vector* block) { matrix_set_block(cthis, index, 0, block); }
Vector* vector_get_block(Vector* cthis, int index, int size) { return matrix_get_block(cthis, index, 0, size, 1);}


//////////////////transpose//////////////
Vector* vector_trans(Vector* cthis) { return matrix_trans(cthis);}

//////////////////operation//////////////
Vector* vector_abs(Vector* cthis) { return matrix_abs(cthis); }
Vector* vector_add(Vector* cthis, Vector* other) { return matrix_add(cthis, other); }
Vector* vector_sub(Vector* cthis, Vector* other) { return matrix_sub(cthis, other); }
Vector* vector_mul(Vector* cthis, Vector* other) { return matrix_mul(cthis, other); }
Vector* vector_div(Vector* cthis, Vector* other) { return matrix_div(cthis, other); }
Vector* vector_mul_scalar(Vector* cthis, DataType scalar) { return matrix_mul_scalar(cthis, scalar); }

//////////////////dot//////////////
DataType vector_dot(Vector* cthis, Vector* other) { return matrix_dot(cthis, other); }
DataType vector_norm(Vector* cthis) { return matrix_norm(cthis); }
Vector* vector_normalize(Vector* cthis) { return matrix_normalize(cthis); }
Vector* vector_cross(Vector* cthis, Vector* other) { return matrix_cross(cthis, other); }

////////////////print///////////////////
void vector_print(Vector* cthis) { matrix_print(vector_trans(cthis));}
