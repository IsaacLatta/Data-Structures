#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct 
{
    struct _node_t* front;
} list_t;

list_t* list_create();
void list_insert(list_t* list, int index, void* data);
void list_remove(list_t* list, int index);
void* list_get(list_t* list, int index);
void list_destroy(list_t* list);
int list_compare(list_t* list1, list_t* list2, int(*cmp_func)(void*, void*));
#endif