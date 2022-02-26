/* Max heap testing utility by Daniel Quintillán and Iván García.
 * This file tests the implementation of the maxheap.h specification.
 */

#include "maxheap.h"
#include <assert.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper functions to test on several array examples

void random_array_fill(int array[], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++)
		array[i] = rand() % size;
}

void ascending_array_fill(int array[], int size) {
	for (int i = 0; i < size; i++)
		array[i] = i;
}

void descending_array_fill(int array[], int size) {
	for (int i = 0; i < size; i++)
		array[i] = size - i;
}

// Helper function that tests if a max heap is valid, that is, if p is a
// parent node of c, then the value of p is greater or equal than the value
// of c. It checks from i down.
int is_max_heap_array(int vector[], int i, int size) {
	// A leaf node is always a max heap (base case). 
	// if i is not an internal node, i is a max heap
	if (i > (size - 1) / 2) 
		return 1;

	// We now know that i has a left child
	// It is more efficient to declare ints here
	int leftchild = 2 * (i + 1) - 1;
	int rightchild = 2 * (i + 1);
	// If i is bigger than its left child	
	return (vector[i] >= vector[leftchild]
		// And its left child is also a max heap
		&& is_max_heap_array(vector, leftchild, size)
		// and its right child either doesn't exist
		&& (rightchild > size ||
		// or its right child is smaller and also a max heap
		(vector[i] >= vector[rightchild]
		&& is_max_heap_array(vector, rightchild, size))));
		// Then i is a max heap
}

// Front-end for the previous helper function 
int is_max_heap(heap *heap_p) {
	return is_max_heap_array(heap_p->vector, 0, heap_p->last);
}

// In a correct implementation, the last of an empty heap is -1.
void test_init_heap(){
	heap *heap_p = malloc(sizeof(heap));
	init_heap(heap_p);
	assert(heap_p->last == -1);
	free(heap_p);
}

// All created heaps must fulfill the max heap conditions
void test_create_heap() {
	int array[32];
	// Tests that 16 random arrays are turned into valid heaps
	for (int i = 0; i < 16; i++) {
		heap *heap_p = malloc(sizeof(heap));
		random_array_fill(array, 32);
		create_heap(array, 32, heap_p);
		// After creating the heap its last element should be correct
		assert(heap_p->last == 31);
		// And it should be a valid max heap
		assert(is_max_heap(heap_p));
		free(heap_p);
	}
}

void test_remove_max() {
	int array[32];
	int counter, i;
	heap *heap_p = malloc(sizeof(heap));
	random_array_fill(array, 32);
	create_heap(array, 32, heap_p);
	// Repeat until the heap is empty
	for (i = 0; i < 32; i++) { 
		// We store the last value of the heap
		counter = heap_p->last;
		remove_max(heap_p);
		// After removing the max element, it must remain a max heap 
		assert(is_max_heap(heap_p));
		// And it last position must be decremented
		assert(heap_p->last == counter - 1);
	}
	// Assert that the size n heap is empty after performing n removals.
	assert(is_empty_heap(heap_p));
	free(heap_p);
}

int main(){
	printf(
	"    +-------------------------------------------------------+\n"
	"    |     Exercise 1 - Testing max heap implementation      |\n"
	"    +-------------------------------------------------------+\n");
	test_create_heap();
	test_init_heap();
	test_remove_max();
	printf("\n");
}
