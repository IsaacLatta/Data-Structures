#include "stack.h"

static struct _node_t {
    struct _node_t* next;
    void* data;
};

static struct _node_t* _node_create(void* data) {
    struct _node_t* node = (struct _node_t*)malloc(sizeof(struct _node_t));
    if (!node)
        return NULL;
    node->next = NULL;
    node->data = data;
    return node;
}

stack_t* stack_create() {
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    if (!stack)
        return NULL;
    stack->top = NULL;
    return stack;
}

void stack_push(stack_t* stack, void* data) {
    struct _node_t* node = _node_create(data);
    if (!node || !stack)
        return;

    if (!stack->top) {
        stack->top = node;
        return;
    }

    node->next = stack->top;
    stack->top = node;
}

void* stack_pop(stack_t* stack) {
    if (!stack || !stack->top)
        return NULL;

    struct _node_t* node = stack->top;
    stack->top = stack->top->next;
    void* data = node->data;
    free(node);
    return data;
}

void stack_destroy(stack_t* stack) {
    if (!stack || !stack->top)
        return;

    struct _node_t* next;
    struct _node_t* node = stack->top;
    while (node != NULL) {
        next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    free(stack);
}

void print_stack(stack_t* stack, void(*print)(void*)) {
    struct _node_t* node = stack->top;
    while (node != NULL) {
        print(node->data);
        node = node->next;
    }
}
