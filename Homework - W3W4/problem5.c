#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void list_append(List *list, int value);
void list_remove(List *list, int value);
void list_print(List *list);
void list_clear(List *list);

int main()
{
    List list = {NULL, NULL};
    while ( 1 ) {
        int x;
        scanf("%d", &x);
        if ( x == -1 ) {
            break;
        }
        list_append(&list, x);
    }
    int k;
    scanf("%d", &k);
    list_remove(&list, k);
    list_print(&list);
    list_clear(&list);
}

void list_print(List *list)
{
    for ( Node *p = list->head; p; p=p->next ) {
        printf("%d ", p->value);
    }
    printf("\n");
}

void list_clear(List *list)
{
    for ( Node *p = list->head, *q; p; p=q ) {
        q = p->next;
        free(p);
    }
}

/* 请在这里填写答案 */

void list_append(List *list, int value){
    if(list -> head == NULL){
        list -> head = (Node *) malloc(sizeof(Node));
        list -> head -> prev = list -> head -> next = NULL;
        list -> head -> value = value;
        list -> tail = list -> head;
    } else {
        list -> tail -> next = (Node *) malloc(sizeof(Node));
        list -> tail -> next -> prev = list -> tail;
        list -> tail = list -> tail -> next;
        list -> tail -> next = NULL;
        list -> tail -> value = value;
    }
}

void list_remove(List *list, int value){
    Node *p = list -> head;
    while(p){
        if(p -> value == value){
            if(p -> prev){
                p -> prev -> next = p -> next;
            }
            if(p -> next){
                p -> next -> prev = p -> prev;
            }
            Node *q = p;
            if(list -> head == p){
                list -> head = p -> next;
            }
            p = p -> next;
            free(q);
        } else {
            p = p -> next;
        }
    }
}