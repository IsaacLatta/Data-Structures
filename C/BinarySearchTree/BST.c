#include "BST.h"

static BST_node_t* _node_create(void* key, void* data) {
    BST_node_t* node = (BST_node_t*)malloc(sizeof(BST_node_t));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->key = key;
    node->right = NULL;
    node->left = NULL;
    return node;
}

BST_t* BST_create(compare_func_t cmp) {
    BST_t *bst = (BST_t*)malloc(sizeof(BST_t));
    if (!bst) {
        return NULL;
    }
    bst->cmp = cmp;
    bst->root = NULL;
    return bst;
}

static BST_node_t* _insert(BST_node_t* node, BST_node_t* new_node, compare_func_t cmp) {
    if (!node) {
        return new_node;
    }
    int res = cmp(new_node->key, node->key);
    if(res == 0) {
    	node->data = new_node->data;
    	free(new_node->key);
    	free(new_node);
    }
    else if (res < 0) {
        node->left = _insert(node->left, new_node, cmp); 
    }
    else if (res > 0){
        node->right = _insert(node->right, new_node, cmp);
    }
    return node;
}

void BST_insert(BST_t* bst, void* key, void* data) {
    BST_node_t* node = _node_create(key, data);
    if (!bst || !node) {
        return;
    }
    bst->root = _insert(bst->root, node, bst->cmp);
}

static void _inorder(BST_node_t* node, process_func_t process, va_list args) {
    if (!node) {
        return;
    }
    _inorder(node->left, process, args);
    process(node, args);
    _inorder(node->right, process, args);
}

static void _preorder(BST_node_t* node, process_func_t process, va_list args) {
    if (!node) {
        return;
    }
    process(node, args);
    _preorder(node->left, process, args);
    _preorder(node->right, process, args);
}

static void _postorder(BST_node_t* node, process_func_t process, va_list args) {
    if (!node) {
        return;
    }
    _postorder(node->left, process, args);
    _postorder(node->right, process, args);
    process(node, args);
}

static BST_node_t* find_min(BST_node_t* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static void _free_node(BST_node_t* node) {
    if(node) {
    	free(node->data);
        free(node->key);
        free(node);
    }
}

static BST_node_t* _delete(BST_node_t* node, void* key, compare_func_t cmp) {
    if (!node) {
        return NULL;
    }

    int res = cmp(key, node->key);
    if (res < 0) {
        node->left = _delete(node->left, key, cmp);
    } else if (res > 0) {
        node->right = _delete(node->right, key, cmp);
    } else if (node->left == NULL && node->right == NULL) {
		_free_node(node);
        return NULL;
	} else if (node->left == NULL) {
        BST_node_t* temp = node->right;
        _free_node(node);
        return temp;
     } else if (node->right == NULL) {
		BST_node_t* temp = node->left;
        _free_node(node);
        return temp;
     } else {
         BST_node_t* min = find_min(node->right);
         node->key = min->key;
         node->data = min->data;
         node->right = _delete(node->right, min->key, cmp);
    }
    return node;
}

void BST_delete(BST_t* bst, void* key) {
    if (!bst || !bst->root || !key) {
        return;
    }
    bst->root = _delete(bst->root, key, bst->cmp);
}

void BST_process(BST_t* bst, int traversal_type, process_func_t process, ...) {
    va_list args;
    va_start(args, process);
    switch (traversal_type) {
        case INORDER:
            _inorder(bst->root, process, args);
            break;
        case PREORDER:
            _preorder(bst->root, process, args);
            break;
        case POSTORDER:
            _postorder(bst->root, process, args);
            break;
    }
    va_end(args);
}

void* BST_get(BST_t* bst, void* key) {
	if(!bst || !bst->root || !key) {
		return NULL;
	}

	int res;
	BST_node_t* current = bst->root;
	while(current != NULL) {
		res = bst->cmp(key, current->key);
		if(res == 0) {
			return current->data;
		}
		else if(res < 0) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return NULL;
}

void _delete_process(BST_node_t* node, va_list args) {
    if (!node) {
        return;
    }
    free(node->data);
    free(node->key);
    free(node);
}

void BST_destroy(BST_t* bst) {
    if (!bst || !bst->root) {
        return;
    }
    BST_process(bst, POSTORDER, _delete_process);
    free(bst);
}
