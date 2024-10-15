#ifndef BST_H
#define BST_H

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3

#include <stdlib.h>
#include <stdarg.h>

typedef struct BST_node {
    struct BST_node* left;    
    struct BST_node* right;   
    void* key;                
    void* data;               
} BST_node_t;

/* Return 0 for match, < 0 for less than, > 0 for greater than */
typedef int (*compare_func_t)(void* key1, void* key2);

typedef struct {
    BST_node_t* root;         
    compare_func_t cmp;       
} BST_t;

typedef void (*process_func_t)(BST_node_t* node, va_list args);

BST_t* BST_create(compare_func_t cmp);
void* BST_get(BST_t* bst, void* key);
void BST_insert(BST_t* bst, void* key, void* data);
void BST_delete(BST_t* bst, void* key);
void BST_process(BST_t* bst, int traversal_type, process_func_t process, ...);
void BST_destroy(BST_t* bst);

#endif  // BST_H
