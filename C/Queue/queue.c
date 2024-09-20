#include "queue.h"

node_t* queue_create_node(void* data)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
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
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->notify, NULL);
    return queue;
}

int queue_size(queue_t* queue)
{
    pthread_mutex_lock(&queue->lock);
    int qsize = queue->size;
    pthread_mutex_unlock(&queue->lock);
    return qsize;
}

void queue_push(queue_t* queue, void* data)
{
    node_t* node = queue_create_node(data);
    if(!node)
    {
        return;
    }

    pthread_mutex_lock(&queue->lock);

    if(queue->back == NULL)
    {
        queue->back = node;
        queue->front = node;
    }
    else
    {
        queue->back->next = node; // Link the old back's next node to new node
        queue->back = node; // Assign the new back node to node
    }

    queue->size++;
    pthread_mutex_unlock(&queue->lock);
    pthread_cond_signal(&queue->notify);
}

void* queue_pop(queue_t* queue)
{
    pthread_mutex_lock(&queue->lock);
    
    while(queue->front == NULL && !queue->close) // Wait for new task
    {
        pthread_cond_wait(&queue->notify, &queue->lock);
    }
    if(queue->close && queue->size == 0)
    {
        pthread_mutex_unlock(&queue->lock);
        return NULL;
    }
    
    node_t* old_node = queue->front;
    void* data = old_node->data;
    queue->front = queue->front->next;

    if(queue->front == NULL) // queue is now empty
    {
        queue->back = NULL;
    }

    queue->size--;
    pthread_mutex_unlock(&queue->lock);
    return data; // Return the node's data
}

void queue_destroy(queue_t* queue)
{
    pthread_mutex_lock(&queue->lock);
    queue->close = 1;
    pthread_mutex_unlock(&queue->lock);
    pthread_cond_broadcast(&queue->notify);

    pthread_mutex_lock(&queue->lock); // retreive lock after all queue_pop calls exit
    node_t* current_node = queue->front;
    node_t* next_node;

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

    pthread_mutex_unlock(&queue->lock);
    pthread_mutex_destroy(&queue->lock);
    pthread_cond_destroy(&queue->notify);
    free(queue);
}
