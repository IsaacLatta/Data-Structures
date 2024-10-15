#include "queue.h"

typedef struct _node
{
    void* data;
    struct _node* next;
} _node_t;

static _node_t* queue_create_node(void* data)
{
    _node_t* node = (_node_t*)malloc(sizeof(_node_t));
    if(!node)
    {
        return NULL;
    } 
    node->data = data;
    node->next = NULL;
    return node;
}

queue_t* queue_create()
{
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if(!queue)
    {
        return NULL;
    }
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

void queue_push(queue_t* queue, void* data)
{
    _node_t* node = queue_create_node(data);
    if(!node)
    {
        return;
    }

    if(queue->back == NULL)
    {
        queue->back = node;
        queue->front = node;
    }
    else
    {
        queue->back->next = node; 
        queue->back = node; 
    }

    queue->size++;
}

void* queue_pop(queue_t* queue)
{
    if(queue->close && queue->size == 0)
    {
        return NULL;
    }
    
    _node_t* old_node = queue->front;
    void* data = old_node->data;
    queue->front = queue->front->next;

    if(queue->front == NULL) // queue is now empty
    {
        queue->back = NULL;
    }

    queue->size--;
    return data; // Return the node's data
}

void queue_destroy(queue_t* queue)
{
    _node_t* current_node = queue->front;
    _node_t* next_node;

    while(current_node != NULL) 
    {
        next_node = current_node->next;
        if(current_node->data != NULL)
        {
            free(current_node->data);
        }
        free(current_node);
        current_node = next_node; 
    }

    free(queue);
}
