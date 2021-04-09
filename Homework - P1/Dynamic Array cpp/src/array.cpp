#include <cstring>
#include <cstdlib>
#include <cassert>
#include "array"

Array::Array(){
    t_size = 0;
    lastidx = 0;
    content = NULL;
}

Array::~Array(){
    t_size = 0;
    free(content);
    content = NULL;
}

int Array::size(){
    return lastidx;
}

void Array::resize(const int &length){
    free(content);
    content = (int*) malloc(sizeof(int) * length);
    t_size = lastidx = length;
}

int& Array::operator [] (const int &index){
    assert(index < lastidx);
    return content[index];
}

void Array::double_inflate(){
    int* newArray = (int*) malloc(sizeof(int) * (t_size << 1));
    memcpy(newArray, content, sizeof(int) * t_size);
    free(content);
    content = newArray;
    t_size <<= 1;
}

void Array::pushback(const int &element){
    if(t_size == 0){
        t_size = 1;
        content = (int*) malloc(sizeof(int));
    } else if(lastidx == t_size){
        double_inflate();
    }
    content[lastidx++] = element;
}

Array Array::operator = (const Array &origin){
    free(content);
    content = (int*) malloc(sizeof(int) * origin.t_size);
    t_size = origin.t_size;
    lastidx = origin.lastidx;
    memcpy(content, origin.content, t_size);
    return *this;
}