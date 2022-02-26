//AUTHORS:
//DANIEL QUINTILLÁN daniel.quintillan
//EMANUELE MERONI emanuele.meroni
//HILDA ROMERO h.rvelo

#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include <sys/time.h>

//Defining function Fibonacci 1 (recursive)
int fib1 (int n) 
{
    if (n<2) return n;
    else return (fib1(n-1)+fib1(n-2));
}
    
//Defining function Fibonacci 2 (iterative)
int fib2 (int n)
{
    int i=1; 
    int j=0;
    int k;
    for (k=1; k<(n+1); k++)
    {
       j=i+j; i=j-i;
    }
return j;
}

//Defining function Fibonacci 3 (iterative)
int fib3(int n)
{
    int i,j,k,t,h;
    i=1;
    h=1;
    t=0;
    j=0;
    k=0;
    
    while (n>0)
    {
        if ((n % 2)!= 0)
        {
            t = j * h;
            j = (i*h) + (j*k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2*k*h) + t;
        k = (k*k) + t;
        n = n / 2; 
    }
return j;
}


//Testing function for the three algorithms
void checkfib () 
{
	int i;
	
    printf("TEST FUNCTION\n Fib1 is --> ");
    for (i = 0; i < 11; i++)
        printf(" %d",fib1(i));
     
    printf("\n Fib2 is --> ");
     for (i = 0; i < 11 ; i++)
        printf(" %d", fib2(i));
     
    printf("\n Fib3 is --> ");
     for (i = 0; i < 11; i++)
        printf(" %d", fib3(i));

    printf("\n\n\n\n");
} 


//Obtaining the current time in microseconds 
double microseconds() 
{
      struct timeval t;
      if (gettimeofday(&t, NULL) < 0)
          return 0.0;
      return (t.tv_usec + t.tv_sec * 1000000.0);
}

//We get the execution time for each function.
//If the measured time is lower than 500 microseconds, 
//we run a loop to compute the arithmetic mean of 1000 executions.
//This is marked in the table with an asterisk.
//Then we compute the values of the bounds to print them on the tables.

void time1()
{
    double t1, t2, t, x, y, z;
    int n;

    printf("           n            t(n)      t(n)/f(n)");
    printf("      t(n)/g(n)      t(n)/h(n)\n");
    
    for (n=2; n<=32; n*=2)
    {   
        char v;
        t1 = microseconds();
        fib1(n);
        t2= microseconds();
        t = t2-t1;
        if (t<500)
        {   
            int i;
            v='*';
            t1 =microseconds();
            for (i=1; i<=1000;i++)
            {
                fib1(n);
            }
            t2=microseconds();
            t = (t2-t1)/1000;
        }
        else 
            v=' ';
        x = t / pow(1.1,n);
        y = t / pow(((1+sqrt(5))/2),n);
        z = t / pow(2, n);
        printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, v, x, y, z);
        }
    }

void time2()
{
    double t1, t2, t, x, y, z;
    int n;

    printf("           n            t(n)      t(n)/f(n)");
    printf("      t(n)/g(n)      t(n)/h(n)\n");
    for (n=1000; n<=10000000; n=n*10)
    {
        char v;
        t1 = microseconds();
        fib2(n);
        t2= microseconds();
        t = t2-t1;
        if (t<500)
        {   
            int i;
            v='*';
            t1 =microseconds();
            for (i=1; i<=1000;i++)
            {
                fib2(n);
            }
            t2=microseconds();
            t = (t2-t1)/1000;
        }
        else v=' ';
        x = t / pow(n,0.8); 
        y = t / n;
        z = t / (n*log(n));        
        printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, v, x, y, z);
    }
}

void time3()
{
    double t1, t2, t, x, y, z;
    int n;

    printf("           n            t(n)       t(n)/f(n)");
    printf("      t(n)/g(n)     t(n)/h(n)\n");
    for (n=1000; n<=10000000; n=n*10)
    {  
        char v;
        t1 = microseconds();
        fib3(n);
        t2= microseconds();
        t = t2-t1;
        if (t<500)
        {   
            int i;
            v='*';
            t1 =microseconds();
            for (i=1; i<=1000;i++)
            {
                fib3(n);
            }
            t2=microseconds();
            t = (t2-t1)/1000;
        }
        x = t / sqrt(log(n));
        y = t / log(n);
        z = t / pow(n, 0.5);
        printf("%12d%15.5f%c%15.6f%15.6f%15.7f\n\n", n, t, v, x, y, z);
    }
}

//We print five tables for each Fibonacci algorithm.
void table(int i)
{
    switch(i)
          {
              int v;              
              case 1: for (v=1; v<=5; v++)
              {
                printf("Table %d of Fibonacci 1:\n", v);
                time1();
              };
              break;
              case 2: for (v=1; v<=5; v++)
              {
                printf("Table %d of Fibonacci 2:\n", v);
                time2();
              }; 
              break;
              case 3: for (v=1; v<=5; v++)
              {
                printf("Table %d of Fibonacci 3:\n", v);
                time3();
              }; 
              break;
          }      
}

int main ()
{
    int i;
    checkfib();
    printf("                             FIBONACCI SEQUENCE\n\n");
    for(i=1; i<=3; i++)
    {
        table(i);
    }
   return 0;
}
