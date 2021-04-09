#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct _node Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void __linkedlist_removeNext(Node *p);

List list_create();
void list_free(List *list);

void list_append(List *list, int v);
void list_insert(List *list, int v);

void list_set(List *list, int index, int v);
int list_get(List *list, int index);

int list_size(List *list);

int list_find(List *list, int v);
void list_remove(List *list, int v);

void list_iterate(List *list, void (*func)(int v));

#endif