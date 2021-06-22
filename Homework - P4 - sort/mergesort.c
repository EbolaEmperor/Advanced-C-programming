#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "mergesort.h"

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

    merge_sort(make_array(a, n));

    gettimeofday(&endtime,0);
    double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    printf("Total time: %d ms\n", (int)(timeuse/1000) );
    print_array(a, n);
    
    return 0;
}

void* merge_sort(void* args){
    struct Array* arr = (struct Array*) args;
    int* a = arr -> a;
    int n = arr -> n, mid = n / 2;

    pthread_t tid = 0;
    if(mid >= 2){
        if(mid < SIZE) merge_sort(make_array(a, mid));
        else pthread_create(&tid, NULL, merge_sort, make_array(a, mid));
    }
    if(n - mid >= 2) merge_sort(make_array(a + mid, n - mid));
    if(tid) pthread_join(tid, NULL);
    merge(arr, mid);
}

void merge(struct Array* arr, int mid){
    int* a = arr -> a;
    int n = arr -> n;
    int* tmp = (int*) malloc(sizeof(int) * n);
    int pl = 0, pr = mid, idx = 0;

    while(pl < mid || pr < n){
        if(pl == mid || pr < n && a[pr] < a[pl]) tmp[idx++] = a[pr++];
        else tmp[idx++] = a[pl++];
    }

    memcpy(a, tmp, sizeof(int) * n);
    free(tmp);
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