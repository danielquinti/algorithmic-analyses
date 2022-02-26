/* Max heap implementation by Daniel Quintillán and Iván García.
 * This file contains the implementation of an array-based max heap data
 * structure.
 */

#include "maxheap.h"

// Helper(static) functions

// Swaps the i-th and j-th elements on the vector(array) representing the heap.
static void swap(heap *heap_p, int i, int j) {
	int temp = heap_p->vector[j];
	heap_p->vector[j] = heap_p->vector[i];
	heap_p->vector[i] = temp;
}

static void percolate_down(heap *heap_p, int i){
	int leftchild, rightchild, j;
	do {
		leftchild = (2 * (i + 1)) - 1; 	// New formulas for indices
		rightchild = 2 * (i + 1);	// starting at 0
		j = i;
		if ((rightchild <= (heap_p->last)) //if not last elem
			// and rightchild is bigger than current
			&& (heap_p->vector[rightchild] > heap_p->vector[i]))
			i = rightchild;
		if ((leftchild <= (heap_p->last))
			&& (heap_p->vector[leftchild]>heap_p->vector[i]))
			i = leftchild; 
		swap(heap_p, j, i);
	} while (j != i);
}

// Implementation of required functions

void create_heap(int array[], int size, heap *heap_p) {
	int i, j;
	// Copy the contents of the array
	for (i = 0; i < size; i++)
		(*heap_p).vector[i] = array[i];
	// this has to be before, as percolate_down makes use of last
	heap_p->last = size - 1;
	// percolate_down the first half of positions in the array
	for (j = size / 2; j >= 0; j--) {
		percolate_down(heap_p, j);
	}
}

// Initializing the heap means just setting its last element to -1 under this
// implementation. It should be used only on empty heaps, as it would wrongly
// change the last element counter otherwise.
void init_heap(heap *heap_p) {
	heap_p->last=-1;
}

int is_empty_heap(heap *heap_p) {
/*	if (heapp->last<0)
		return 1;
	else return 0;
*/
	return (heap_p->last < 0);
}

// Needs explaining comments
int remove_max(heap *heap_p) {
	int x;
	if (is_empty_heap(heap_p))
		return -1;
	else {
		x = heap_p->vector[0];
		heap_p->vector[0] = heap_p->vector[heap_p->last];
		heap_p->last--;
		if (heap_p->last >= 0)
			percolate_down(heap_p, 0);
		return x;
	}
}
