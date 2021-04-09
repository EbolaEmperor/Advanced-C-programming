
#include <stdio.h>
#include <stdlib.h>
typedef struct node        /*这个结构类型包括三个域 */
{    int number;        /*猴子的编号*/
    int mydata;        /* 猴子的定数 */
    struct node *next; /* 指向下一只猴子的指针 */
} linklist;
linklist *CreateCircle( int n );
linklist *DeleteNext(linklist *p);   /* 删除单循环链表的p所指的下一个结点 */

/* 提示： 你所有的代码将由系统插入在此处 */

int main()
{
    linklist *head;
    int i,n;
    scanf("%d",&n); 
    head = CreateCircle(n); /*创建单向循环链表，返回最后一个结点的指针 */
    printf("The king is monkey[%d].\n", KingOfMonkey(n,head));
    return 0;
}
/* 请在这里填写答案 */

linklist * CreateCircle(int n){
    linklist *head = NULL, *p = NULL;
    for(int i = 1, x; i <= n; i ++){
        scanf("%d", &x);
        if(head == NULL){
            head = (linklist *) malloc(sizeof(linklist));
            p = head;
            p -> mydata = x;
            p -> number = i;
            p -> next = head;
        } else {
            p -> next = (linklist *) malloc(sizeof(linklist));
            p = p -> next;
            p -> mydata = x;
            p -> number = i;
            p -> next = head;
        }
    }
    return head;
}

linklist * DeleteNext(linklist *p){
    printf("Delete No:%d\n", p -> next -> number);
    linklist *q = p -> next;
    p -> next = q -> next;
    free(q);
    return p;
}

int KingOfMonkey(int n, linklist *head){
    linklist *h = head;
    while(head -> next != h){
        head = head -> next;
    }
    int d = head -> mydata;
    while(head -> next != head){
        for(int i = 0; i < d - 1; i ++){
            head = head -> next;
        }
        d = head -> next -> mydata;
        head = DeleteNext(head);
    }
    return head -> number;
}