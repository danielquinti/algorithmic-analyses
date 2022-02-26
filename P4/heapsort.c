#include "maxheap.h"
void heap_sort(int array[], int size){
	int i;
	heap *heap_p = malloc(sizeof(heap));
	create_heap(array, size, heap_p);
	for (i = size-1; i >= 0; i--)
		array[i] = remove_max(heap_p);
	free(heap_p);
}
