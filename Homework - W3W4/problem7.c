#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */

List insert(List p, ElementType x){
    p -> Next = (List) malloc(sizeof(struct Node));
    p = p -> Next;
    p -> Data = x;
    p -> Next = NULL;
    return p;
}

List removeNext(List p){
    List q = p -> Next;
    p -> Next = q -> Next;
    free(q);
    return p;
}

//注意：Read()是本地测试需要的，在提交时应当删去
List Read(){
    List head = (List) malloc(sizeof(struct Node));
    List p = head;
    ElementType n, x;
    scanf("%d", &n);
    while(n--){
        scanf("%d", &x);
        p = insert(p, x);
    }
    return head;
}

//注意：Print()是本地测试需要的，在提交时应当删去
void Print(List L){
    L = L -> Next;
    if(L == NULL){
        printf("NULL\n");
        return;
    }
    while(L){
        printf("%d ", L -> Data);
        L = L -> Next;
    }
    printf("\n");
}

List Merge(List L1, List L2){
    List head = (List) malloc(sizeof(struct Node));
    List p = head;
    while(L1 -> Next || L2 -> Next){
        if(L1 -> Next == NULL || (L1 -> Next && L2 -> Next && L2 -> Next -> Data < L1 -> Next -> Data)){
            p = insert(p, L2 -> Next -> Data);
            L2 = removeNext(L2);
        } else {
            p = insert(p, L1 -> Next -> Data);
            L1 = removeNext(L1);
        }
    }
    return head;
}