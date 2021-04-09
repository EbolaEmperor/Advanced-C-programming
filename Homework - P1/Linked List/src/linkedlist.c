#include <stdlib.h>
#include "linkedlist.h"

struct _node {
    int value;
    struct _node *next;
};

List list_create(){
    List *list = (List*) malloc(sizeof(List));
    list -> head = NULL;
    list -> tail = NULL;
    return *list;
}

void list_free(List *list){
    Node *iterator = list -> head;
    Node *tail = list -> tail;
    while(iterator != tail){
        Node *p = iterator -> next;
        free(iterator);
        iterator = p;
    }
    free(iterator);
    list -> head = NULL;
    list -> tail = NULL;
}

void list_append(List *list, int v){
    if(list -> head == NULL){
        list -> head  = (Node*) malloc(sizeof(Node));
        list -> head -> value = v;
        list -> head -> next = NULL;
        list -> tail = list -> head;
    } else {
        list -> tail -> next  = (Node*) malloc(sizeof(Node));
        list -> tail = list -> tail -> next;
        list -> tail -> value = v;
        list -> tail -> next = NULL;
    }
}

void list_insert(List *list, int v){
    if(list -> head == NULL){
        list -> head  = (Node*) malloc(sizeof(Node));
        list -> head -> value = v;
        list -> head -> next = NULL;
        list -> tail = list -> head;
    } else {
        Node *p  = (Node*) malloc(sizeof(Node));
        p -> value = v;
        p -> next = list -> head;
        list -> head = p;
    }
}

void list_set(List *list, int index, int v){
    Node *p = list -> head;
    for(int i = 0; i < index; i ++){
        p = p -> next;
    }
    p -> value = v;
}

int list_get(List *list, int index){
    Node *p = list -> head;
    for(int i = 0; i < index; i ++){
        p = p -> next;
    }
    return p -> value;
}

int list_size(List *list){
    Node *iterator = list -> head;
    Node *tail = list -> tail;
    if(iterator == NULL){
        return 0;
    }
    int size = 1;
    while(iterator != tail){
        iterator = iterator -> next;
        size ++;
    }
    return size;
}

int list_find(List *list, int v){
    Node *iterator = list -> head;
    Node *tail = list -> tail;
    if(iterator == NULL){
        return -1;
    }
    int index = 0;
    while(iterator != tail){
        if(iterator -> value == v){
            return index;
        }
        iterator = iterator -> next;
        index ++;
    }
    if(tail -> value == v){
        return index;
    }
    return -1;
}

void __linkedlist_removeNext(Node *p){
    Node *q = p -> next;
    p -> next = q -> next;
    free(q);
}

void list_remove(List *list, int v){
    Node *head = (Node*) malloc(sizeof(Node));
    head -> next = list -> head;
    Node *iterator = head;
    Node *tail = list -> tail;
    while(iterator -> next != tail){
        if(iterator -> next -> value == v){
            __linkedlist_removeNext(iterator);
        } else {
            iterator = iterator -> next;
        }
    }
    if(tail -> value == v){
        free(tail);
        iterator -> next = NULL;
        list -> tail = (iterator == head) ? NULL : iterator;
    }
    list -> head = head -> next;
    free(head);
}

void list_iterate(List *list, void (*func)(int v)){
    Node *iterator = list -> head;
    Node *tail = list -> tail;
    while(iterator != tail){
        func(iterator -> value);
        iterator = iterator -> next;
    }
    func(tail -> value);
}