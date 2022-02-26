/*Authors: Daniel Quintillán (daniel.quintillan)
           Emanuele Meroni (emanuele.meroni) 
           Hilda Romero (h.rvelo)
*/


#include "Both.h"

#ifndef THRESHOLD
#define THRESHOLD 1
#endif


void swap (int v[], int a, int b){
  int aux;
  aux = v[a];
  v[a] = v[b];
  v[b] = aux;
}

void Median3 (int V[], int i, int j){
    int k = (i + j) / 2 ; /* precondition: i < j */
    if (V[k] > V[j]) swap (V,k, j) ;
    if (V[k] > V[i]) swap (V,k, i) ;
    if (V[i] > V[j]) swap (V,i, j) ;
}

void quick_sort_aux(int v[], int left, int right){
	if(left+THRESHOLD <= right){
    Median3(v,left,right);
		int pivot = v[left];
		int i=left, j= right;

		do{
			do i++; while(v[i]<pivot);
			do j--; while(v[j]>pivot);
			swap(v, i, j);
		}
    while(j>i);

		swap(v, i, j);
		swap(v, left, j);

		quick_sort_aux(v,left,j-1),
		quick_sort_aux(v,j+1, right);
	}
}

void quick_sort(int v [], int n) {
  quick_sort_aux(v, 0, n-1);
  if (THRESHOLD > 1)
    ins_sort(v, n);
}

void check(int n){
  int v [n];
  for (int i = 0; i < 3; i++){
    switch (i) {
      case 0: {
        random_init(v,n);
        printf("Random initialization\n");
        break;
      }
        case 1:{
          ascending_init(v,n);
          printf("Ascending initialization\n");
          break;
        }
        case 2: {
          descending_init(v,n);
          printf("Descending initialization\n");
          break;
        }
    }
    printarray(v,n);
    printf("Quicksort\n");quick_sort(v, n);
    printarray(v,n);
  }
}

double timeunder500RQ(int n){
  int v [n];
  double ta, tb, t1, t2, t;
  int i, j;
  int k = 1000;

  ta = microseconds();
  for (i = 0; i<=k; i++){
    random_init(v,n);
    quick_sort(v, n);
  }
  tb = microseconds();
  t1 = tb - ta;
  ta = microseconds();
  for (j = 0; j<=k; j++){
    random_init(v,n);
  }
  tb = microseconds();
  t2 = tb - ta;
  t = (t1 - t2)/k;
  return t;
}


void timeQuicksortR(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
  random_init(v,n);
  t1 = microseconds();
  quick_sort(v, n);
  t2= microseconds();
  t = t2-t1;
  if (t<500){
    ast = '*';
    t = timeunder500RQ(n);
  }
  x = t / (pow(n,0.65)*log(n));
  y = t / (pow(n,1.009482)*log(n));
  z = t / (pow(n,1.35)*log(n));
  printf("%12d%15.5f%c%15.7f%15.7f%15.9f\n\n", n, t, ast, x, y, z);
}


double timeunder500DQ(int n){
  int v [n];
  double ta, tb, t1, t2, t;
  int i, j;
  int k = 1000;
  
  ta = microseconds();
  for (i = 0; i<=k; i++){
    descending_init(v,n);
    quick_sort(v, n);
  }
  tb = microseconds();
  t1 = tb - ta;
  ta = microseconds();
  for (j = 0; j<=k; j++){
    descending_init(v,n);
  }
  tb = microseconds();
  t2 = tb - ta;
  t = (t1 - t2)/k;
  return t;
}


void timeQuicksortD(int n){
  char ast = ' ';
  int v[n];
  double t1, t2, t, x, y, z;
  descending_init(v,n);
  t1 = microseconds();
  quick_sort(v, n);
  t2= microseconds();
  t = t2-t1;
  if (t<500){
    ast = '*';
    t = timeunder500RQ(n);
  }
  x = t / (pow(n,0.75)*log(n));
  y = t / (pow(n,0.972)*log(n));
  z = t / (pow(n,1.5)*log(n));
  printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

double timeunder500AQ(int n){
  int v [n];
  double ta, tb, t1, t2, t;
  int i, j;

  int k = 1000;
  ta = microseconds();
  for (i = 0; i<=k; i++){
    ascending_init(v,n);
    quick_sort(v, n);
  }
  tb = microseconds();
  t1 = tb - ta;
  ta = microseconds();
  for (j = 0; j<=k; j++){
    ascending_init(v,n);
  }
  tb = microseconds();
  t2 = tb - ta;
  t = (t1 - t2)/k;
  return t;
}


void timeQuicksortA(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
  ascending_init(v,n);
  t1 = microseconds();
  quick_sort(v, n);
  t2= microseconds();
  t = t2-t1;
  if (t<500){
    ast = '*';
    t = timeunder500AQ(n);
  }
  x = t / (pow(n,0.6)*log(n));
  y = t / (pow(n,0.96)*log(n));
  z = t / (pow(n,1.4)*log(n));
  printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printQuicksortTables(){
  int n;
  printf("Quicksort: Random initialization\n\n");
  tableHeader();
  for(n=500; n<100000;n=n*2){
    timeQuicksortR(n);
  }
  printf("Quicksort: Descending initialization\n\n");
  tableHeader();
  for(n=500; n<100000;n=n*2){
    timeQuicksortD(n);
  }
  printf("Quicksort: Ascending initialization\n\n");
  tableHeader();
  for(n=500; n<100000;n=n*2){
    timeQuicksortA(n);
  }
}

int main(){
  check(10);
  printQuicksortTables();   
  return 0;
}
