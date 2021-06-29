#define SIZE (1<<15)

struct Array{
    int *a;
    int n;
};

void* quick_sort(void*);
int divide(struct Array*);

void* make_array(int*, int);
void print_array(int*, int);
void swap(int*, int*);
unsigned Rand();