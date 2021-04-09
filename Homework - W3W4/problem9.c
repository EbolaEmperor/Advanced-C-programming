#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *deletem( struct ListNode *L, int m );
void printlist( struct ListNode *L )
{
     struct ListNode *p = L;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}

int main()
{
    int m;
    struct ListNode *L = readlist();
    scanf("%d", &m);
    L = deletem(L, m);
    printlist(L);

    return 0;
}

/* 你的代码将被嵌在这里 */

struct ListNode * insert(struct ListNode *p, int x){
    p -> next = (struct ListNode *) malloc(sizeof(struct ListNode));
    p = p -> next;
    p -> data = x;
    p -> next = NULL;
    return p;
}

struct ListNode * removeNext(struct ListNode *p){
    struct ListNode *q = p -> next;
    p -> next = q -> next;
    free(q);
    return p;
}

struct ListNode *readlist(){
    struct ListNode *head = (struct ListNode *) malloc(sizeof(struct ListNode));
    struct ListNode *p = head;
    int x;
    scanf("%d", &x);
    while(x != -1){
        p = insert(p, x);
        scanf("%d", &x);
    }
    return head -> next;
}

struct ListNode *deletem(struct ListNode *L, int m){
    struct ListNode *head = (struct ListNode *) malloc(sizeof(struct ListNode));
    struct ListNode *p = head;
    head -> next = L;
    while(p -> next){
        if(p -> next -> data == m){
            p = removeNext(p);
        } else {
            p = p -> next;
        }
    }
    return head -> next;
}