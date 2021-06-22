#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "sort.h"

/**********************************************
 *                  主函数
 **********************************************/

int main(){
    int n, *a;
    struct Array *b[THREAD_NUM];
    pthread_t tid[THREAD_NUM];
    
    FILE * fp = fopen("data.in", "r");
    FILE * fmode = fopen("mode.ini", "r");
    fscanf(fmode, "%c", &MODE);
    fscanf(fp, "%d", &n);
    a = (int*) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%d", a + i);
    }
    fclose(fmode);
    fclose(fp);
    
    struct timeval starttime, middletime, endtime;
    gettimeofday(&starttime,0);

    SIZE = n / THREAD_NUM;
    for(int i = 0; i < THREAD_NUM; i ++){
        b[i] = (struct Array *) malloc(sizeof(struct Array));
        b[i] -> a = a + i * SIZE;
        b[i] -> n = (i == THREAD_NUM - 1) ? (n - i * SIZE) : SIZE;
        pthread_create(&tid[i], NULL, sort_thread, (void*)(b[i]) );
    }
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_join(tid[i] , NULL);
    }

    gettimeofday(&endtime,0);
    double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    printf("[Main] Sorting time of threads: %d ms\n", (int)(timeuse/1000) );
    middletime = endtime;

    nth_merge(a, n, b);

    gettimeofday(&endtime,0);
    timeuse = 1000000*(endtime.tv_sec - middletime.tv_sec) + endtime.tv_usec - middletime.tv_usec;
    printf("[Main] Merging time: %d ms\n", (int)(timeuse/1000) );
    timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    printf("[Main] Totle Time: %d ms\n", (int)(timeuse/1000) );
    
    print_array(a, n);
    free(a);
    
    return 0;
}

/**********************************************
 *                  基本函数
 **********************************************/

void swap(int *x, int *y){
    int t = *x;
    *x = *y;
    *y = t;
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

unsigned Rand(){
	static unsigned x = 19260817;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

/**********************************************
 *                 线程函数
 **********************************************/

void* sort_thread(void *args){
    struct Array *arr = (struct Array *) args;
    if(MODE == 'Q'){
        printf("[Thread] Mode: Quick Sort    length = %d\n", arr -> n);
        quick_sort(arr -> a, arr -> n);
    }
    else if(MODE == 'M'){
        printf("[Thread] Mode: Merge Sort    length = %d\n", arr -> n);
        merge_sort(arr -> a, arr -> n);
    }
    else printf("undefined mode.");
}

/**********************************************
 *               快速排序部分
 **********************************************/

void quick_sort(int *a, int n){
    _quick_sort_(a, n);
}

void _quick_sort_(int *a, int n){
    int t = Rand() % n;
    swap(&a[0], &a[t]);
    int l = 0, r = n - 1, x = a[0];
    while(l < r){
        while(l < r && a[r] >= x) r--;
        if(l < r) a[l] = a[r];
        while(l < r && a[l] <= x) l++;
        if(l < r) a[r] = a[l];
    }
    a[l] = x;
    if(l) _quick_sort_(a, l);
    if(n - l - 1) _quick_sort_(a + l + 1, n - l - 1);
}

/**********************************************
 *               归并排序部分
 **********************************************/

void merge_sort(int *a, int n){
    int *tmp = (int*) malloc(sizeof(int) * n);
    //printf("[Thread] Malloc successful.  tmp: %p\n", tmp);
    _merge_sort_(a, n, tmp);
    free(tmp);
}

void _merge_sort_(int *a, int n, int *tmp){
    int mid = n / 2;
    if(mid >= 2) _merge_sort_(a, mid, tmp);
    if(n - mid >= 2) _merge_sort_(a + mid, n - mid, tmp + mid);
    int pl = 0, pr = mid, idx = 0;
    while(pl < mid || pr < n){
        if(pl == mid || pr < n && a[pr] < a[pl]) tmp[idx++] = a[pr++];
        else tmp[idx++] = a[pl++];
    }
    memcpy(a, tmp, sizeof(int) * n);
}

/**********************************************
 *               多路归并部分
 **********************************************/

void nth_merge(int *a, int n, struct Array *b[]){
    int p[THREAD_NUM] = {0};
    int* tmp = (int *) malloc(sizeof(int) * n);
    int cnt = 0;
    
    while(1){
        //找到每一路开头元素中最小的那个
        int idx = -1;
        for(int i = 0; i < THREAD_NUM; i++){
            if(p[i] == b[i] -> n) continue;
            if(idx == -1 || b[i] -> a[p[i]] < b[idx] -> a[p[idx]]) idx = i;
        }
        tmp[cnt++] = b[idx] -> a[p[idx]++];

        //检查是否每一路都已完成归并
        int check = 1;
        for(int i = 0; i < THREAD_NUM; i++){
            if(p[i] < b[i] -> n){
                check = 0;
                break;
            }
        }
        if(check) break;
    }

    memcpy(a, tmp, sizeof(int) * n);
    free(tmp);
}