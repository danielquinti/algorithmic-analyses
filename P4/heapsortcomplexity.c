#include "heapsort.h"
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <time.h>

void random_array_fill(int array[],int size){
	int i;
	srand(time(NULL));
	for (i=0;i<size;i++)
		array[i]=rand()%size;
}

void ascending_array_fill(int array[],int size){
	int i;
	for (i=0;i<size;i++)
	array[i]=i;
}

void descending_array_fill(int array[],int size){
	int i;
	for (i=0;i<size;i++)
		array[i]=size-i;
}

double microseconds() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

double time_under_500(int n,int array[]) {
	double t1,t2;
	int j;
	int k=1000;
	t1=microseconds();
	for (j = 0; j < k; j++)
		heap_sort(array, n);
	t2=microseconds();
	return (t2-t1)/1000;
}

void heap_sort_complexity() {
	int array[SIZE], n, j;
	char init[32];
	heap *heap_p = malloc(sizeof(heap));
	double t1, t2, t, f, g, h;
	char l; // Indicates if the nth run was a loop
	for (j = 1; j <= 3; j++) {
	if (j == 1)
		strcpy(init, "ascending initialization");
	if (j == 2)
		strcpy(init, "descending initialization");
	if (j == 3)
		strcpy(init, "random initialization");
	printf(
	" +-------------------------------------------------------------+\n"
	" |              Heapsort - %-32s    |\n"
	" +-------------------------------------------------------------+\n"
	" |   f(n)=(n^0.8)*log(n); g(n)=n*log(n); h(n)=(n^1.2)*log(n)   |\n"
	" +--------+------------+---+-----------+-----------+-----------+\n"
	" |   n    |       t(n) | l | t(n)/f(n) | t(n)/g(n) | t(n)/h(n) |\n"
	" +--------+------------+---+-----------+-----------+-----------+\n",
	init);
	for (n = 100; n <=12800 ; n *= 2) {
		if (j == 1)
			ascending_array_fill(array, n);
		if (j == 2)
			descending_array_fill(array, n);
		if (j == 3)
			random_array_fill(array, n);
		l = ' ';
		t1=microseconds();
		heap_sort(array,n);
		t2=microseconds();
		t=t2-t1;
		if (t < 500) {
			l = '*';
			t=time_under_500(n,array);
		}
		f = t / (pow(n,0.8)*log(n));
		g = t / (n*log(n));
		h = t / (pow(n,1.2)*log(n));
		printf(" | %6d | %10.1f | %c | %9.5f | %9.5f | %9.5f |\n",
			n, t, l, f, g, h);
	}
	printf(
	" +--------+------------+---+-----------+-----------+-----------+\n"
	" |                         | Underest. | Tight     | Overest.  |\n"
	" +-------------------------+-----------+-----------+-----------+\n");
	}
	free(heap_p);
}


int main(){
	int i;
	printf(
	"    +-------------------------------------------------------+\n"
	"    |     Exercise 4 - Calculating heapsort complexity      |\n"
	"    +-------------------------------------------------------+\n");
	for(i=0;i<4;i++)
		heap_sort_complexity();
	printf("\n");

}
