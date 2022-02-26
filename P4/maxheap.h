/* Max heap implementation by Daniel Quintillán and Iván García.
 * This file contains the interface to an array-based max heap data structure.
 */

#ifndef MAXHEAP
#define MAXHEAP

#include <stdlib.h>  
#include <stdio.h>

#define SIZE 128000

// Heaps contain a representation vector and a last position counter.
// The last position should be the last position of the vector that contains
// valid data, or -1 if the heap is empty. 
typedef struct{
	int vector[SIZE];
	int last;
} heap;

// Creates a max heap of size "size" from the contents of array[].
void create_heap(int array[], int size, heap *heap_p);

// Initializes the heap for use. Must be done after malloc and before use.
void init_heap(heap *heap_p);

// Returns 1 if the heap pointed to by heap_p is empty, 0 otherwise.
int is_empty_heap(heap *heap_p);

// Removes the maximum element of the heap and keeps the remaining elements
// as a valid heap.
int remove_max(heap *heap_p);

#endif // MAXHEAP
