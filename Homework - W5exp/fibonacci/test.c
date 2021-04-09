#include <stdio.h>
#include <stdlib.h>

#include "fib.h"

#define JUDGE(x, c, s) {\
    FILE *fp = fopen(argv[1], "a");\
    if ( fp ) {\
        fprintf(fp, "%s\t", s);\
        if ( x ) {\
            credit += c;\
            fprintf(fp, "PASS %d %d\n", c, credit);\
        } else {\
            fprintf(fp, "FAIL 0\n");\
        }\
        fclose(fp);\
    }\
}

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "w");
    if ( !fp ) {
        exit(-1);
    }
    fclose(fp);

    int credit=0;
    beginFib();

    fp = fopen("in.txt", "r");
    if ( !fp ) {
        exit(-1);
    }
    
    while (1) {
        int x,y,z;
        fscanf(fp, "%d %d", &x, &z);
        if ( x== -1 ) {
            break;
        }
        if ( x == 0 ) {
            beginFib();
            y = nextFib();
        }
        for ( int i=0; i<x; i++ ) {
            y=nextFib();
        }
        char word[80];
        sprintf(word, "next %d time(s)", x);
        JUDGE(y==z, 1, word);
    }
    fclose(fp);

    fp = fopen(argv[1], "a");
    if ( fp ) {
        fprintf(fp, "%d\n", credit);
        fclose(fp);
    }
}

#include "fib.h"