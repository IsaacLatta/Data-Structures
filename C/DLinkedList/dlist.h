#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

typedef struct 
{
    struct _node_t* front;
    struct _node_t* back;
    int size;
} dlist_t;

dlist_t* dlist_create();
void dlist_insert(dlist_t* dlist, int index, void* data);
void dlist_remove(dlist_t* dlist, int index);
void* dlist_get(dlist_t* dlist, int index);
void dlist_destroy(dlist_t* dlist);
#endif