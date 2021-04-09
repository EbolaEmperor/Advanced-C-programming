#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist(); /*裁判实现，细节不表*/
struct ListNode *reverse( struct ListNode *head );
void printlist( struct ListNode *head )
{
     struct ListNode *p = head;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}

int main()
{
    struct ListNode  *head;

    head = createlist();
    head = reverse(head);
    printlist(head);

    return 0;
}

// Insert a node after p and return it's pointer
struct ListNode * insert(struct ListNode *p, int x){
    struct ListNode *q = p -> next;
    p -> next = (struct ListNode *) malloc(sizeof(struct ListNode));
    p = p -> next;
    p -> data = x;
    p -> next = q;
    return p;
}

struct ListNode * newHead(){
    struct ListNode *head;
    head = (struct ListNode *) malloc(sizeof(struct ListNode));
    head -> data = -1;
    head -> next = NULL;
    return head;
}

struct ListNode * createlist(){
    struct ListNode *head = newHead(), *p = head;
    int x;
    scanf("%d", &x);
    do{
        p = insert(p, x);
        scanf("%d", &x);
    }while(x != -1);
    return head -> next;
}

/* 你的代码将被嵌在这里 */

struct ListNode * reverse(struct ListNode *head){
    struct ListNode *p = NULL;
    for(; head; head = head -> next){
        struct ListNode *q = (struct ListNode *) malloc(sizeof(struct ListNode));
        q -> data = head -> data;
        q -> next = p;
        p = q;
    }
    return p;
}