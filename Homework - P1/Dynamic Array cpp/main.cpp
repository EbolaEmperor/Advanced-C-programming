#include "array"
#include <cstdio>

int main(){
    Array a;
    int x;
    scanf("%d", &x);
    while(x != -1){
        a.pushback(x);
        scanf("%d", &x);
    }
    for(int i = 0; i < a.size(); i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}