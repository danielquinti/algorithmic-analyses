default:
	gcc -Wall -o testmaxheap testmaxheap.c maxheap.c
	gcc -Wall -o maxheapcomplexity maxheapcomplexity.c maxheap.c -lm
	gcc -Wall -o testheapsort testheapsort.c heapsort.c maxheap.c
	gcc -Wall -o heapsortcomplexity heapsortcomplexity.c heapsort.c maxheap.c -lm
	
clean:
	rm heapsortcomplexity maxheapcomplexity testheapsort testmaxheap
run:
	gcc -Wall -o testmaxheap testmaxheap.c maxheap.c
	gcc -Wall -o maxheapcomplexity maxheapcomplexity.c maxheap.c -lm
	gcc -Wall -o testheapsort testheapsort.c heapsort.c maxheap.c
	gcc -Wall -o heapsortcomplexity heapsortcomplexity.c heapsort.c maxheap.c -lm
	./testmaxheap
	./maxheapcomplexity
	./testheapsort
	./heapsortcomplexity
e1:
	gcc -Wall -o testmaxheap testmaxheap.c maxheap.c
	./testmaxheap
e2:
	gcc -Wall -o maxheapcomplexity maxheapcomplexity.c maxheap.c -lm
	./maxheapcomplexity
e3:
	gcc -Wall -o testheapsort testheapsort.c heapsort.c maxheap.c
	./testheapsort
e4:
	gcc -Wall -o heapsortcomplexity heapsortcomplexity.c heapsort.c maxheap.c -lm
	./heapsortcomplexity
