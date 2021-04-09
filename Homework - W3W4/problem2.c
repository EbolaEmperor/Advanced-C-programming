#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist();
struct ListNode *deleteeven( struct ListNode *head );
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
    struct ListNode *head;

    head = createlist();
    head = deleteeven(head);
    printlist(head);

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

// Remove the node after p and free it
struct ListNode * removeNode(struct ListNode *p){
    struct ListNode *q = p -> next;
    p -> next = q -> next;
    q -> next = NULL;
    free(q);
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

struct ListNode * deleteeven(struct ListNode *L){
    struct ListNode *head, *p;
    head = newHead();
    head -> next = L;
    p = head;
    while(p -> next){
        if(p -> next -> data % 2 == 0){
            p = removeNode(p);
        } else {
            p = p -> next;
        }
    }

    return head -> next;
}