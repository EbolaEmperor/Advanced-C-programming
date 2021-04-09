#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist(); /*裁判实现，细节不表*/
struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2);
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
    struct ListNode  *list1, *list2;

    list1 = createlist();
    list2 = createlist();
    list1 = mergelists(list1, list2);
    printlist(list1);

    return 0;
}

/* 你的代码将被嵌在这里 */

struct ListNode * insert(struct ListNode *p, int x){
    p -> next = (struct ListNode *) malloc(sizeof(struct ListNode));
    p = p -> next;
    p -> next = NULL;
    p -> data = x;
    return p;
}

//注意，函数createlist本地测试时需要，提交时需删去
struct ListNode * createlist(){
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

struct ListNode * mergelists(struct ListNode * L1, struct ListNode * L2){
    struct ListNode *head = (struct ListNode *) malloc(sizeof(struct ListNode));
    struct ListNode *p = head;
    while(L1 || L2){

        if(L1 == NULL || (L1 && L2 && L2 -> data < L1 -> data)){
            p = insert(p, L2 -> data);
            L2 = L2 -> next;
        } else {
            p = insert(p, L1 -> data);
            L1 = L1 -> next;
        }
    }
    return head -> next;
}