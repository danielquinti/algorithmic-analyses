/* Heapsort testing utility by Daniel Quintillán and Iván García.
 * This file tests the validity of the implementation of the heapsort.h
 * specification.
 */

#include "heapsort.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void random_array_fill(int array[], int size) {
	for (int i = 0; i < size; i++)
		array[i] = rand() % 99;
}

int is_sorted(int array[],int size){
	int i;
	for(i=1;i<size;i++)
	if(array[i-1]>array[i])
		return 0;
	return 1;
}

void test_heap_sort(){
	int array[32], i;
	random_array_fill(array, 16);
	printf(
	" +-------------------------------------------------------------+\n"
	" | Sorting: ");
	for (i = 0; i < 15; i++)
		printf("%02d,", array[i]);
	printf("%02d", array[15]);
	printf(
	"    |\n"
	//" +-------------------------------------------------------------+\n"
	" | Sorted : ");
	heap_sort(array,16);
	assert(is_sorted(array,16));
	for (i = 0; i < 15; i++)
		printf("%02d,", array[i]);
	printf("%02d", array[15]);
	printf(
	"    |\n"
	" +-------------------------------------------------------------+\n");
}

int main(){
	int i;
	srand(time(NULL));	
	printf(
	"    +-------------------------------------------------------+\n"
	"    |             Exercise 3 - Testing heapsort             |\n"
	"    +-------------------------------------------------------+\n");
	for (i = 0; i < 4; i++)
		test_heap_sort();
	printf("\n");
}
