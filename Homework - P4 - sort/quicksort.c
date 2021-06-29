#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "quicksort.h"

int main(){
    int n, *a;
    
    FILE * fp = fopen("data.in", "r");
    fscanf(fp, "%d", &n);
    a = (int*) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%d", a + i);
    }
    fclose(fp);

    struct timeval starttime, endtime;
    gettimeofday(&starttime,0);

    quick_sort(make_array(a, n));

    gettimeofday(&endtime,0);
    double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    printf("Total time: %d ms\n", (int)(timeuse/1000) );
    print_array(a, n);
    
    return 0;
}

void* quick_sort(void* args){
    struct Array* arr = (struct Array*) args;
    int* a = arr -> a;
    int n = arr -> n;

    int mid = divide(arr);
    pthread_t tid = 0;
    if(mid >= 2){
        if(mid < SIZE) quick_sort(make_array(a, mid));
        else pthread_create(&tid, NULL, quick_sort, make_array(a, mid));
    }
    if(n - mid - 1 >= 2) quick_sort(make_array(a + mid + 1, n - mid - 1));
    if(tid) pthread_join(tid, NULL);
}

int divide(struct Array* arr){
    int* a = arr -> a;
    int n = arr -> n;
    swap(&a[0], &a[Rand() % n]);
    int l = 0, r = n - 1, x = a[0];

    while(l < r){
        while(l < r && a[r] >= x) r--;
        if(l < r) a[l] = a[r];
        while(l < r && a[l] <= x) l++;
        if(l < r) a[r] = a[l];
    }
    a[l] = x;
    return l;
}

void* make_array(int *a, int n){
    struct Array* arr = (struct Array*) malloc(sizeof(struct Array));
    arr -> a = a;
    arr -> n = n;
    return (void*) arr;
}

void print_array(int *a, int n){
    FILE * fp = fopen("result.out", "w");
    fprintf(fp, "%d", a[0]);
    for(int i = 1; i < n; i++){
        fprintf(fp, " %d", a[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

void swap(int *x, int *y){
    int t = *x;
    *x = *y;
    *y = t;
}

unsigned Rand(){
	static unsigned x = 19260817;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}