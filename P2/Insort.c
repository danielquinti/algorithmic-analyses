/*Authors: Daniel Quintillán (daniel.quintillan)
           Emanuele Meroni (emanuele.meroni) 
           Hilda Romero (h.rvelo)
*/

#include "Both.h"

double timeunder500RI(int n){
    int v [n];
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 1000;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      random_init(v,n);
      ins_sort(v, n);
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



void timeInsortR(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
        random_init(v,n);
        t1 = microseconds();
        ins_sort(v, n);
        t2= microseconds();
        t = t2-t1;
        if (t<500){
           ast = '*';
           t = timeunder500RI(n);
        }
        x = t / (pow(n,1.8));
        y = t / (pow(n,2));
        z = t / (pow(n,2.2));
        printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);

}

double timeunder500AI(int n){
    int v [n];
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 1000;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      ascending_init(v,n);
      ins_sort(v, n);
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


void timeInsortA(int n){
    int v[n];
    double t1, t2, t, x, y, z;
    char ast = ' ';
          ascending_init(v,n);
          t1 = microseconds();
          ins_sort(v, n);
          t2= microseconds();
          t = t2-t1;
          if (t<500){
             ast = '*';
             t = timeunder500AI(n);
          }
          x = t / (pow(n,0.8));
          y = t / n;
          z = t / (pow(n,1.2));
          printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

double timeunder500DI(int n){
  int v [n];
  double ta, tb, t1, t2, t;
  int i, j;
  int k = 1000;
  ta = microseconds();
  for (i = 0; i<=k; i++){
    descending_init(v,n);
    ins_sort(v, n);
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


void timeInsortD(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
  descending_init(v,n);
  t1 = microseconds();
  ins_sort(v, n);
  t2= microseconds();
  t = t2-t1;
  if (t<500){
    ast = '*';
    t = timeunder500DI(n);
  }
  x = t / (pow(n,1.8));
  y = t / (pow(n,2));
  z = t / (pow(n,2.2));
  printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
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
    printf("Insort\n");ins_sort(v,n);
    printarray(v,n);
  }
 }

void printInsortTables(){
  int n;
  printf("Insort: Random initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timeInsortR(n);
  }
  printf("Insort: Descending initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timeInsortD(n);
  }
  printf("Insort: Ascending initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timeInsortA(n);
  }
}

int main(){
  check(10);
  printInsortTables();
  return 0;
}
