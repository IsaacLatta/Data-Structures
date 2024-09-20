#include "dlist.h"

typedef struct _node_t
{
    void* data;
    struct _node_t* next;
    struct _node_t* prev;
} _node_t;

_node_t* _node_create(void* data)
{
    _node_t* node = (_node_t*)malloc(sizeof(_node_t));
    if (!node)
        return NULL;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

dlist_t* dlist_create()
{
    dlist_t* dlist = (dlist_t*)malloc(sizeof(dlist_t));
    if (!dlist)
        return NULL;

    dlist->front = NULL;
    dlist->back = NULL;
    dlist->size = 0;
    return dlist;
}

static void _insert_back(dlist_t* dlist, _node_t* new_node, _node_t* prev_node)
{
    prev_node->next = new_node;
    new_node->prev = prev_node;
    dlist->back = new_node;
}

static void _insert(dlist_t* dlist, int index, _node_t* new_node)
{
    _node_t* node = dlist->front;
    _node_t* prev_node = NULL;    
    for (int i = 0; i < index && node != NULL; i++)
    {
        prev_node = node;
        node = node->next;
    }
    
    if (!node) // End of list
    {
        _insert_back(dlist, new_node, prev_node);
        return;
    }

    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = node;
    node->prev = new_node;
}

static void _insert_front(dlist_t* dlist, _node_t* new_node)
{
    new_node->next = dlist->front;
        new_node->prev = NULL;

    if(dlist->front != NULL) // Case: list not empty
        dlist->front->prev = new_node;
    dlist->front = new_node;
    if(!dlist->back) // Case: list empty
        dlist->back = new_node;
}

void dlist_insert(dlist_t* dlist, int index, void* data)
{
    if(index < 0)
        return;

    _node_t* new_node = _node_create(data);
    if (!new_node)
        return;

    if (!dlist->front || index == 0)
    {
        _insert_front(dlist, new_node);
        return;
    }

    _insert(dlist, index, new_node);
}

static void _remove(dlist_t* dlist, int index)
{
    _node_t* prev_node = NULL;
    _node_t* node = dlist->front;
    for (int i = 0; i < index && node != NULL; i++)
    {
        prev_node = node;
        node = node->next;
    }

    if (!node) // Index out of bounds
        return;

    prev_node->next = node->next;
    if(prev_node->next != NULL)
        prev_node->next->prev = prev_node;
    else
        dlist->back = prev_node;
    
    free(node->data);
    free(node);
}

static void _remove_front(dlist_t* dlist)
{
    _node_t* node = dlist->front;
    dlist->front = dlist->front->next;

    if(dlist->front != NULL) 
        dlist->front->prev = NULL; // dlist not empty
    else 
        dlist->back = NULL; // dlist now empty

    free(node->data);
    free(node);
}

void dlist_remove(dlist_t* dlist, int index)
{
    if (index < 0 || !dlist->front)
        return;

    if (index == 0) 
    {
        _remove_front(dlist);
        return;
    }

    _remove(dlist, index);    
}

void* dlist_get(dlist_t* dlist, int index)
{
    if (!dlist->front|| index < 0) // Empty dlist
        return NULL;

    _node_t* node = dlist->front;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
        if (!node) 
            return NULL;
    }
    return node->data;
}

void dlist_destroy(dlist_t* dlist) // Iterate backwards
{
    _node_t* next = NULL;
    _node_t* node = dlist->back;
    while(node != NULL)
    {
        next = node->prev;
        free(node->data);
        free(node);
        node = next;
    }
    free(dlist);
}