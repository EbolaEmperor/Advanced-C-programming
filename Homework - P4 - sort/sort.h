#define THREAD_NUM 4

struct Array{
    int *a;
    int n;
};
int SIZE;
char MODE;

void swap(int*, int*);
void print_array(int*, int);
unsigned Rand();

void* sort_thread(void*);

void quick_sort(int*, int);
void _quick_sort_(int*, int);

void merge_sort(int*, int);
void _merge_sort_(int*, int, int*);

void nth_merge(int*, int, struct Array *[]);