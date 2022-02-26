#include "Both.h"

void sort (int v [], int n) {
    int increments[11]={88573,29524,9841,3280,1093,364,121,40,13,4,1};
    int k,i,j,temp,currentincrement;
    for (k=0;k<11;k++){
        currentincrement=increments[k];
        for (i=currentincrement;i<=(n-1);i++){
            temp=v[i];
            j=i;
            while (j>=currentincrement && v[j-currentincrement]>temp) {
                v[j]=v[j-currentincrement];
                j=j-currentincrement;
            }
            v[j]=temp;    
        }
    }
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
    printf("Shell sort\n");sort(v,n);
    printarray(v,n);
    }
}

double timeunder500RI(int n){
    int v [n];
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 1000;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      random_init(v,n);
      sort(v, n);
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



void timesortR(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
        random_init(v,n);
        t1 = microseconds();
        sort(v, n);
        t2= microseconds();
        t = t2-t1;
        if (t<500){
           ast = '*';
           t = timeunder500RI(n);
        }
        x = t / n;
        y = t / (pow(n,1.2));
        z = t / (pow(n,1.4));
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
      sort(v, n);
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


void timesortA(int n){
    int v[n];
    double t1, t2, t, x, y, z;
    char ast = ' ';
          ascending_init(v,n);
          t1 = microseconds();
          sort(v, n);
          t2= microseconds();
          t = t2-t1;
          if (t<500){
             ast = '*';
             t = timeunder500AI(n);
          }
          x = t / pow(n,0.83);
          y = t / pow(n,1.13);
          z = t / pow(n,1.43);
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
    sort(v, n);
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


void timesortD(int n){
  int v[n];
  double t1, t2, t, x, y, z;
  char ast = ' ';
  descending_init(v,n);
  t1 = microseconds();
  sort(v, n);
  t2= microseconds();
  t = t2-t1;
  if (t<500){
    ast = '*';
    t = timeunder500DI(n);
  }
  x = t / (pow(n,0.8));
  y = t / (pow(n,1.1));
  z = t / (pow(n,1.4));
  printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}


void printShellSortTables(){
  int n;
  printf("Shell sort: Random initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timesortR(n);
  }
  printf("Shell sort: Descending initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timesortD(n);
  }
  printf("Shell sort: Ascending initialization\n\n");
  tableHeader();
  for(n = 10; n < 1000000; n=n*10){
    timesortA(n);
  }
}

int main(){
int i;
init_seed();
check(10);
for(i=1;i<5;i++){
    printShellSortTables();
}
}
