#include "maxheap.h"
#include <math.h>
#include <time.h>
#include <sys/time.h>

void ascending_array_fill(int array[], int size) {
        for (int i = 0; i < size; i++)
                array[i] = i;
}

double microseconds() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

double time_under_500(int n,int array[], heap *heap_p){
    double t1, t2;
    int k = 1000, i;
    t1 = microseconds();
            for (i = 0; i < k; i++)
                create_heap(array, n, heap_p);
            t2 = microseconds();
            return (t2 - t1) / 1000;
}

void create_heap_complexity() {
	int array[SIZE], n;
	heap *heap_p = malloc(sizeof(heap));
	printf(
	" +-------------------------------------------------------------+\n"
	" |                       Heap Creation                         |\n"
	" +-------------------------------------------------------------+\n"
	" |                  f(n)=n^0.8; g(n)=n; h(n)=n^1.2             |\n"
	" +--------+------------+---+-----------+-----------+-----------+\n"
	" |    n   |       t(n) | l | t(n)/f(n) | t(n)/g(n) | t(n)/h(n) |\n"
	" +--------+------------+---+-----------+-----------+-----------+\n");
	double t1, t2, t, f, g, h;
	char l; /* Indicates if the nth run was a loop */
	for (n = 100; n <= SIZE ; n *= 2) {
		ascending_array_fill(array, n);
		l = ' ';
		t1 = microseconds();
		create_heap(array, n, heap_p);
		t2 = microseconds();
		t = t2 - t1;
		if (t < 500) {
			l = '*';
			t=time_under_500(n, array, heap_p);
		}
		f = t / pow(n, 0.8);
		g = t / n;
		h = t / pow(n, 1.2);
		printf(" | %6d | %10.1f | %c | %9.5f | %9.5f | %9.5f |\n",
			n, t, l, f, g, h);
	}
	printf(
	" +--------+------------+---+-----------+-----------+-----------+\n"
	" |                         | Underest. | Tight     | Overest.  |\n"
	" +-------------------------+-----------+-----------+-----------+\n");
    free(heap_p);
}

int main() {
	printf(
	"    +-------------------------------------------------------+\n"
	"    |    Exercise 2 - Calculating create heap complexity    |\n"
	"    +-------------------------------------------------------+\n");
	create_heap_complexity();
	printf("\n");
}
