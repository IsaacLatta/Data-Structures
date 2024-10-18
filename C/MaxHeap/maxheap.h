#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef void(*process_func_t)(void*, va_list args);
typedef int(*compare_func_t)(void*, void*);

typedef struct {
	void** array;
	int capacity;
	int size;
	compare_func_t cmp;	
} maxheap_t;

maxheap_t* maxheap_create(compare_func_t cmp);
void maxheap_insert(maxheap_t* heap, void* data);
void* maxheap_extract(maxheap_t* heap);
void maxheap_process(maxheap_t* heap, process_func_t process, ...);
void maxheap_destroy(maxheap_t*);

#endif
