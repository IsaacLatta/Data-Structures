#include "maxheap.h"

maxheap_t* maxheap_create(compare_func_t cmp) {
	maxheap_t* heap = (maxheap_t*)malloc(sizeof(maxheap_t));
	if(!heap) {
		return NULL;
	}
	heap->cmp = cmp;
	heap->size = 0;
	heap->capacity = 10;
	heap->array = (void**)malloc(sizeof(void*)*heap->capacity);
	if(!heap->array) {
		return NULL;
	}
	return heap;
}

static void _swap(void** node1, void** node2) {
	void* temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

static void** _resize(void** array, int new_capacity) {
	void** new_array = (void**)realloc(array, new_capacity*sizeof(void*));
	if(!new_array) {
		return NULL;
	}
	return new_array;
}

static void _heapify_up(maxheap_t* heap, int index) {
	int parent_index = index / 2;
	while(index != 0 && heap->cmp(heap->array[index], heap->array[parent_index]) > 0) {
		_swap(&heap->array[index], &heap->array[parent_index]);
		index = parent_index;
		parent_index = index / 2;
	}
}

static void _heapify_down(maxheap_t* heap, int index) {
	int largest = index;
	int left = 2*index + 1;
	int right = 2*index + 2;

	if(left < heap->size && heap->cmp(heap->array[left], heap->array[largest]) > 0) {
		largest =  left;
	}
	if(right < heap->size && heap->cmp(heap->array[right], heap->array[largest]) > 0) {
		largest = right;
	}
	if(largest != index) {
		_swap(&heap->array[largest], &heap->array[index]);
		_heapify_down(heap, largest);
	}
}

void maxheap_insert(maxheap_t* heap, void* data) {
	if(!heap || !data || !heap->array) {
		return;
	}

	if(heap->size == heap->capacity) {
		void** new_array = _resize(heap->array, heap->capacity*2);
		if(!new_array) {
			return;
		}
		heap->array = new_array;
		heap->capacity = heap->capacity*2;
	}
	heap->array[heap->size] = data;
	_heapify_up(heap, heap->size);
	heap->size++;
}

void maxheap_destroy(maxheap_t* heap) {
	if(!heap || !heap->array) {
		return;
	}
	for(int i = 0; i < heap->size; i++) {
		free(heap->array[i]);
	}
	free(heap->array);
	free(heap);
}

void maxheap_process(maxheap_t* heap, process_func_t process, ...) {
	if(!heap || !heap->array) {
		return;
	}

	va_list args;
	va_start(args, process);
	for(int i = 0; i < heap->size; i++) {
		process(heap->array[i], args);
	}
	va_end(args);
}

void* maxheap_extract(maxheap_t* heap) {
	if(!heap || !heap->array || heap->size == 0) {
		return NULL;
	}

	void* root = heap->array[0]; 
	_swap(&heap->array[0], &heap->array[heap->size - 1]);
	heap->size--;
	_heapify_down(heap, 0);
	return root;
}
