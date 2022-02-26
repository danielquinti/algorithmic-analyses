/*Authors: Daniel Quintillán (daniel.quintillan)
           Emanuele Meroni (emanuele.meroni) 
           Hilda Romero (h.rvelo)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <inttypes.h>
#ifndef Both_H_   /* Include guard */
#define Both_H_

void init_seed();
void random_init(int v [], int n);
void ascending_init(int v [], int n);
void descending_init(int v [], int n);
int isSorted(int v[], int n);
void printarray(int v[], int n);
double microseconds();
void tableHeader();
void ins_sort (int v [], int n);


#endif
