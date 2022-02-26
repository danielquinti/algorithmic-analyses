#include "Both.h"

void init_seed() {
  srand(time(NULL));
}

void random_init(int v [], int n) {
  int i, m=2*n+1;
  for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
}

void ascending_init(int v [], int n) {
  int i;
  for (i=0; i < n; i++)
    v[i] = i;
}

void descending_init(int v [], int n){
  int j;
  for (j = 0; j < n; j++)
    v[j] = n - j;
}

int isSorted(int v[], int n){
  for (int i=1; i<n; i++){
    if (v[i-1] >v[i])
      return 0;
  }
   return 1;
}

void printarray(int v[], int n){
  for (int i=0; i<n; i++){
    printf("%d, ",v[i]);
  }
  printf("\n");
  printf("sorted? %d\n",isSorted(v,n));
}

double microseconds()
{
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0)
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tableHeader(){
  printf("           n            t(n)      t(n)/f(n)");
  printf("      t(n)/g(n)      t(n)/h(n)\n");
}
