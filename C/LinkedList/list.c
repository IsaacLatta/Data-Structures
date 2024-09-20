#include "list.h"

typedef struct _node_t
{
    void* data;
    struct _node_t* next;
} _node_t;

_node_t* _node_create(void* data)
{
    _node_t* node = (_node_t*)malloc(sizeof(_node_t));
    if (!node)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

list_t* list_create()
{
    list_t* list = (list_t*)malloc(sizeof(list_t));
    if (!list)
        return NULL;

    list->front = NULL;
    return list;
}

void list_insert(list_t* list, int index, void* data)
{
    _node_t* new_node = _node_create(data);
    if (!new_node)
        return;
    
    if (!list->front || index == 0)
    {
        new_node->next = list->front;  
        list->front = new_node;
        return;
    }

    _node_t* prev_node = NULL;
    _node_t* node = list->front;
    for (int i = 0; i < index && node != NULL; i++)
    {
        prev_node = node;
        node = node->next;
    }
    
    if (!prev_node || (!node && index > 0))
        return;

    prev_node->next = new_node;
    new_node->next = node;
}

void list_remove(list_t* list, int index)
{
    if (!list->front) // Empty list
        return;
    
    _node_t* prev_node = NULL;
    _node_t* node = list->front;

    if (index == 0)
    {
        list->front = list->front->next;
        free(node->data);
        free(node);
        return;
    }

    for (int i = 0; i < index && node != NULL; i++)
    {
        prev_node = node;
        node = node->next;
    }

    if (!node) // Index out of bounds
        return;

    prev_node->next = node->next;
    free(node->data);
    free(node);
}

void* list_get(list_t* list, int index)
{
    if (!list->front) // Empty list
        return NULL;

    _node_t* node = list->front;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
        if (!node) // Index out of bounds
            return NULL;
    }

    return node->data;
}

void list_destroy(list_t* list)
{
    _node_t* next = NULL;
    _node_t* node = list->front;
    while(node != NULL)
    {
        next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    free(list);
}

int list_compare(list_t* list1, list_t* list2, int(*cmp_func)(void*, void*))
{
    if(!list1->front && !list2->front)
        return 1;

    _node_t* node_2 = list1->front;
    _node_t* node_1 = list2->front;
    while(node_2 != NULL && node_1 != NULL)
    {
        if(!cmp_func(node_1->data, node_2->data)) 
            return 0;
        
        node_1 = node_1->next;
        node_2 = node_2->next;
    }

    if((!node_1 && node_2) || (node_1 && !node_2))
        return 0;

    return 1;
}
