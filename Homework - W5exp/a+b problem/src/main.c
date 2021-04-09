#include <stdio.h>

int main(){
    FILE *inp = fopen("in.txt", "r");
    int a, b;
    fscanf(inp, "%d%d", &a, &b);
    fclose(inp);

    FILE *outp = fopen("out.txt", "w");
    fprintf(outp, "%d\n", a+b);
    fclose(outp);
    return 0;
}