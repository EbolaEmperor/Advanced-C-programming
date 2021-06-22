#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    FILE *fp = fopen("data.in", "w");
    srand(time(0));
    int n = 10000000;
    fprintf(fp, "%d\n", n);
    for(int i = 0; i < n; i++){
        fprintf(fp, "%d ", rand());
    }
    return 0;
}