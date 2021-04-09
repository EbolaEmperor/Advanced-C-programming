#include "fib.h"

int fib1, fib2;

void beginFib(){
    fib1 = 0;
    fib2 = 1;
}

int nextFib(){
    int fib3 = fib1 + fib2;
    fib1 = fib2;
    fib2 = fib3;
    return fib3;
}