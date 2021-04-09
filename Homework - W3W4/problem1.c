#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *getodd( struct ListNode **L );
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
    struct ListNode *L, *Odd;
    L = readlist();
    Odd = getodd(&L);
    printlist(Odd);
    printlist(L);

    return 0;
}

/* 你的代码将被嵌在这里 */

// Insert a node after p and return it's pointer
struct ListNode * insert(struct ListNode *p, int x){
    struct ListNode *q = p -> next;
    p -> next = (struct ListNode *) malloc(sizeof(struct ListNode));
    p = p -> next;
    p -> data = x;
    p -> next = q;
    return p;
}

// Remove the node after p but not free it, return it's pointer
struct ListNode * removeNode(struct ListNode *p){
    struct ListNode *q = p -> next;
    p -> next = q -> next;
    q -> next = NULL;
    return q;
}

struct ListNode * newHead(){
    struct ListNode *head;
    head = (struct ListNode *) malloc(sizeof(struct ListNode));
    head -> data = -1;
    head -> next = NULL;
    return head;
}

struct ListNode * readlist(){
    struct ListNode *head = newHead(), *p = head;
    int x;
    scanf("%d", &x);
    do{
        p = insert(p, x);
        scanf("%d", &x);
    }while(x != -1);
    return head -> next;
}

struct ListNode *getodd(struct ListNode **L){
    struct ListNode *head, *p, *oddHead, *q;
    head = newHead();
    head -> next = *L;
    p = head;
    oddHead = newHead();
    q = oddHead;
    while(p -> next){
        if(p -> next -> data % 2 == 1){
            struct ListNode *waste = removeNode(p);
            q = insert(q, waste -> data);
            free(waste);
        } else {
            p = p -> next;
        }
    }

    *L = head -> next;
    return oddHead -> next;
}