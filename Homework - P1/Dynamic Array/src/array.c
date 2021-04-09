#include "array.h"
#include <stdlib.h>
#include <string.h>

Array array_create(){
    Array *p = (Array*) malloc(sizeof(Array));
    p -> size = BLOCK_SIZE;
    p -> content = (int*) malloc(sizeof(int) * BLOCK_SIZE);
    return *p;
}

void array_free(Array* array){
    array -> size = 0;
    free(array -> content);
    array -> content = NULL;
}

int array_size(const Array *array){
    return array -> size;
}

void array_inflate(Array *array){
    Array *newArray = (Array*) malloc(sizeof(Array));
    newArray -> size = array -> size + BLOCK_SIZE;
    newArray -> content = (int*) malloc(sizeof(int) * newArray -> size);
    memcpy(newArray -> content, array -> content, sizeof(int) * array -> size);
    array_free(array);
    (*array) = (*newArray);
}

void array_double(Array *array){
    Array *newArray = (Array*) malloc(sizeof(Array));
    newArray -> size = array -> size * 2;
    newArray -> content = (int*) malloc(sizeof(int) * newArray -> size);
    memcpy(newArray -> content, array -> content, sizeof(int) * array -> size);
    array_free(array);
    (*array) = (*newArray);
}

int array_get(const Array *array, int index){
    return array -> content[index];
}

void array_set(Array *array, int index, int value){
    array -> content[index] = value;
}

Array array_clone(const Array *array){
    Array *newArray = (Array*) malloc(sizeof(Array));
    newArray -> size = array -> size;
    newArray -> content = (int*) malloc(sizeof(int) * newArray -> size);
    memcpy(newArray -> content, array -> content, sizeof(int) * newArray -> size);
    return *newArray;
}