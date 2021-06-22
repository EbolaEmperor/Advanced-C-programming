#define SIZE (1<<20)

struct Array{
    int *a;
    int n;
};

void* merge_sort(void*);
void merge(struct Array*, int);

void* make_array(int*, int);
void print_array(int*, int);