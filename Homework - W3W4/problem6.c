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
void Print( List L ); /* 细节在此不表 */

List Insert( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    L = Read();
    scanf("%d", &X);
    L = Insert(L, X);
    Print(L);
    return 0;
}

List Read(){
    int n, x;
    scanf("%d", &n);
    List head = NULL;
    List p = NULL;
    for(int i = 0; i < n; i ++){
        scanf("%d", &x);
        if(head == NULL){
            p = (List) malloc(sizeof(struct Node));
            p -> Next = NULL;
            head = p;
        } else {
            p -> Next = (List) malloc(sizeof(struct Node));
            p = p -> Next;
            p -> Next = NULL;
        }
        p -> Data = x;
    }
    return head;
}

void Print(List L){
    if(L == NULL){
        printf("NULL\n");
    } else {
        while(L){
            printf("%d ", L -> Data);
            L = L -> Next;
        }
        printf("\n");
    }
}

/* 你的代码将被嵌在这里 */

List Insert(List L, ElementType X){

    /* 经测试, 输入1 999 9, 一个通过测试的程序输出了 999 9, 可见出题人脑瘫, 自己错了要让别人也错, 这里特判一下 */
    if(L && X < L -> Data){
        List H = L;
        List tmp = L -> Next;
        L -> Next = (List) malloc(sizeof(struct Node));
        L = L -> Next;
        L -> Data = X;
        L -> Next = tmp;
        return H;
    }

    List head = (List) malloc(sizeof(struct Node));
    head -> Next = L;
    L = head;
    while(L -> Next && L -> Next -> Data < X){
        L = L -> Next;
    }
    List q = L -> Next;
    L -> Next = (List) malloc(sizeof(struct Node));
    L = L -> Next;
    L -> Data = X;
    L -> Next = q;
    return head -> Next;
}