#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define KEY_LENGTH 30
#define SYNONYMS_LENGTH 300
#include <string.h>


/*******************HASH FUNCTIONS*******************************************/
int nhash(char *key, int tablesize) {
  if (strcmp(key, "ANNE")==0) return 7;
  if (strcmp(key, "JOHN")==0) return 7;
  if (strcmp(key, "LOUISE")==0) return 7;
  return 6;
}

int hashA(char *key, int tableSize) {
  int i, value = key[0], n = MIN(8, strlen(key));
  for (i = 1; i < n; i++)
    value += key[i];
  return value % tableSize;
}


int hashB(char *key, int tableSize) {
   int i, n = MIN(8, strlen(key));
   unsigned int value = key[0];
   for (i = 1; i < n; i++)
     value = (value<<5) + key[i]; /* the shift by 5 bits is equivalent to */
   return value % tableSize; /* multiplying by 32 */
}
/****************************************************************************/


/***********************STRUCTURE AND TYPE DECLARATION***********************/
typedef struct entry_ {
    int occupied;
    char key [KEY_LENGTH];
    char synonyms [SYNONYMS_LENGTH];
} entry;

typedef struct {
  char key [KEY_LENGTH];
  char synonyms [SYNONYMS_LENGTH];
} item;

typedef int pos;

typedef entry *closed_table;

typedef item *closed_dictionary;

/****************************************************************************/

/****************EXERCISE 1-COLLISION RESOLUTION FUNCTIONS*******************/
unsigned int LinearProbing(int initial_pos, int try_number){
    return initial_pos+try_number;
}


unsigned int QuadraticProbing(int initial_pos, int try_number){
    return initial_pos + pow(try_number,2);
}

unsigned int DoubleHashing(int initial_pos, int try_number){
    return initial_pos+try_number*(10007-(initial_pos % 10007));
}


void init_closed(closed_table *dictionary, int size){
  int i;
  for(i=0;i<size;i++){
    (*dictionary)[i].occupied = 0;
  }
}

pos find_closed(char *key, closed_table dictionary, int size, int *collisions, int (*hash)(char *, int), unsigned int (*collision_resolution)(int initial_pos, int try_number)){
  int i;
  int j = (*hash)(key, size);
  int h = (*hash)(key, size);
  for (i = 1;((dictionary[h].occupied==1) && (strcmp(dictionary[h].key, key)!=0));i++){
      h = (*collision_resolution)(j,i) % size;
      (*collisions)++;
  }
  if (strcmp(dictionary[h].key, key)==0)
        return h;
  else return -1;
}

int insert_closed(char *key, char *synonyms, closed_table *dictionary, int size, int (*hash)(char *, int), unsigned int (*collision_resolution)(int initial_pos, int try_number)){
    int i;
    int collisions = 0;
    int j = (*hash)(key, size);
    int h = (*hash)(key, size);
    for (i = 1; ((*dictionary)[h].occupied == 1); i++){
        h = (*collision_resolution)(j,i) % size;
        collisions++;
    }
    if ((*dictionary)[h].occupied == 0){
      strcpy((*dictionary)[h].key, key);
      strcpy((*dictionary)[h].synonyms, synonyms);
      (*dictionary)[h].occupied = 1;
    }
    return collisions;
}

void show_closed(closed_table dictionary, int size){
  for(int i = 0; i<size; i++){
        printf("%d- ",i);
        if (dictionary[i].occupied==1){
            printf("(%s: %s)",dictionary[i].key,dictionary[i].synonyms);
        }
        printf("\n");
  }
}

void CheckLinear(){
  int collisions=0;
  int totalcollisionsinsertion = 0;
  closed_table d = malloc (11 * sizeof(entry));
  init_closed(&d, 11);
  totalcollisionsinsertion+= insert_closed("ANNE","none",&d, 11, nhash, LinearProbing);
  totalcollisionsinsertion+= insert_closed("WILLIAM","none",&d, 11, nhash, LinearProbing);
  totalcollisionsinsertion+= insert_closed("JOHN","none",&d, 11, nhash, LinearProbing);
  totalcollisionsinsertion+= insert_closed("LOUISE","none",&d, 11, nhash, LinearProbing);
  totalcollisionsinsertion+= insert_closed("ROSE","none",&d, 11, nhash, LinearProbing);
  totalcollisionsinsertion+= insert_closed("JO","none",&d, 11, nhash, LinearProbing);
  printf("***LINEAR CLOSED TABLE\n");
  show_closed(d, 11);
  printf("Total number of collisions inserting elements: %d\n\n", totalcollisionsinsertion);

  printf("When looking for: ANNE, I find: %s", d[find_closed("ANNE",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: WILLIAM, I find: %s", d[find_closed("WILLIAM",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JOHN, I find: %s", d[find_closed("JOHN",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: LOUISE, I find: %s", d[find_closed("LOUISE",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: ROSE, I find: %s", d[find_closed("ROSE",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JO, I find: %s", d[find_closed("JO",d, 11, &collisions, nhash, LinearProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;
  free(d);
}

void CheckQuadratic(){
  int collisions=0;
  int totalcollisionsinsertion = 0;
  closed_table d = malloc (11 * sizeof(entry));
  init_closed(&d, 11);
  totalcollisionsinsertion+= insert_closed("ANNE","none",&d, 11, nhash, QuadraticProbing);
  totalcollisionsinsertion+= insert_closed("WILLIAM","none",&d, 11, nhash, QuadraticProbing);
  totalcollisionsinsertion+= insert_closed("JOHN","none",&d, 11, nhash, QuadraticProbing);
  totalcollisionsinsertion+= insert_closed("LOUISE","none",&d, 11, nhash, QuadraticProbing);
  totalcollisionsinsertion+= insert_closed("ROSE","none",&d, 11, nhash, QuadraticProbing);
  totalcollisionsinsertion+= insert_closed("JO","none",&d, 11, nhash, QuadraticProbing);
  printf("***QUADRATIC CLOSED TABLE\n");
  show_closed(d, 11);
  printf("Total number of collisions inserting elements: %d\n\n", totalcollisionsinsertion);

  printf("When looking for: ANNE, I find: %s", d[find_closed("ANNE",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: WILLIAM, I find: %s", d[find_closed("WILLIAM",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JOHN, I find: %s", d[find_closed("JOHN",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: LOUISE, I find: %s", d[find_closed("LOUISE",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: ROSE, I find: %s", d[find_closed("ROSE",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JO, I find: %s", d[find_closed("JO",d, 11, &collisions, nhash, QuadraticProbing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;
  free(d);
}

void CheckDouble(){
  int collisions=0;
  int totalcollisionsinsertion = 0;
  closed_table d = malloc (11 * sizeof(entry));
  init_closed(&d, 11);
  totalcollisionsinsertion+= insert_closed("ANNE","none",&d, 11, nhash, DoubleHashing);
  totalcollisionsinsertion+= insert_closed("WILLIAM","none",&d, 11, nhash, DoubleHashing);
  totalcollisionsinsertion+= insert_closed("JOHN","none",&d, 11, nhash, DoubleHashing);
  totalcollisionsinsertion+= insert_closed("LOUISE","none",&d, 11, nhash, DoubleHashing);
  totalcollisionsinsertion+= insert_closed("ROSE","none",&d, 11, nhash, DoubleHashing);
  totalcollisionsinsertion+= insert_closed("JO","none",&d, 11, nhash, DoubleHashing);
  printf("***DOUBLE HASHING CLOSED TABLE\n");
  show_closed(d, 11);
  printf("Total number of collisions inserting elements: %d\n\n", totalcollisionsinsertion);

  printf("When looking for: ANNE, I find: %s", d[find_closed("ANNE",d, 11, &collisions, nhash,DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: WILLIAM, I find: %s", d[find_closed("WILLIAM",d, 11, &collisions, nhash, DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JOHN, I find: %s", d[find_closed("JOHN",d, 11, &collisions, nhash, DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: LOUISE, I find: %s", d[find_closed("LOUISE",d, 11, &collisions, nhash, DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: ROSE, I find: %s", d[find_closed("ROSE",d, 11, &collisions, nhash, DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;

  printf("When looking for: JO, I find: %s", d[find_closed("JO",d, 11, &collisions, nhash, DoubleHashing)].key);
  printf(", collisions: %d\n", collisions );
  collisions = 0;
  free(d);
}
/****************************************************************************/

/**************EXERCISE 2- FUNCTION TO READ THE TXT FILE*********************/

int read_synonyms(item data[]) {
    char c;
    int i, j;
    FILE *myfile;
    if ((myfile = fopen("sinonimos.txt", "r")) == NULL) {
        printf("Error opening 'sinonimos.txt'\n");
        return(EXIT_FAILURE);
    }
    for (i = 0; fscanf(myfile, "%s", data[i].key) != EOF; i++) {
        if ((c = fgetc(myfile)) != '\t') {
            printf("Error reading a tab\n");
            return(EXIT_FAILURE);
        }
        for (j = 0; (c = fgetc(myfile)) != '\n'; j++) {
            if (j < SYNONYMS_LENGTH - 1)
                data[i].synonyms[j] = c;
        }
        data[i].synonyms[MIN(j, SYNONYMS_LENGTH -1)] = '\0';
    }
    if (fclose(myfile) != 0) {
        printf("Error closing the file\n");
        return(EXIT_FAILURE);
    }
    return(i);
}

void show_dictionary(closed_dictionary dictionary, int size){
  for(int i = 0; i<size; i++){
        printf("%d- ",i);
        printf("(%s: %s)",dictionary[i].key,dictionary[i].synonyms);
        printf("\n");
  }
}

closed_table checkDictionaryLinearA(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashA, LinearProbing);
  }
  return f;
}

closed_table checkDictionaryQuadraticA(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashA, QuadraticProbing);
  }
  return f;
}

closed_table checkDictionaryDoubleHashingA(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashA, DoubleHashing);
  }
  return f;
}

closed_table checkDictionaryLinearB(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashB, LinearProbing);
  }
  return f;
}

closed_table checkDictionaryQuadraticB(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashB, QuadraticProbing);
  }
  return f;
}

closed_table checkDictionaryDoubleHashingB(closed_dictionary d, int *totalcollisionsinsertion){
  int i;
  char k[KEY_LENGTH];
  char s[SYNONYMS_LENGTH];
  closed_table f = malloc (38197 * sizeof(entry));
  init_closed(&f, 38197);
  for(i=0;i<19062;i++){
    strcpy(k, d[i].key);
    strcpy(s, d[i].synonyms);
    (*totalcollisionsinsertion)+= insert_closed(k,s,&f, 38197, hashB, DoubleHashing);
  }
  return f;
}

/*********************************EXERCISE 3*****************************/
void tableHeader(){
  printf("           n            t(n)      t(n)/f(n)");
  printf("      t(n)/g(n)      t(n)/h(n)\n");
}

void init_seed() {
  srand(time(NULL));
}

double microseconds(){
      struct timeval t;
      if (gettimeofday(&t, NULL) < 0)
          return 0.0;
      return (t.tv_usec + t.tv_sec * 1000000.0);
}

double timeunder500LA(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, LinearProbing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeLinearA(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, LinearProbing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500LA(d, f, n);
      }
      x = t / (log(n));
      y = t / n;
      z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printLinearTableA(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Linear hashing with hash function A \n");
  f = checkDictionaryLinearA(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeLinearA(d, f,n);
  }
  free(f);
}

double timeunder500LB(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, LinearProbing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeLinearB(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, LinearProbing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500LB(d, f, n);
      }
      x = t / (log(n));
      y = t / n;
      z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printLinearTableB(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Linear hashing with hash function B \n");
  f = checkDictionaryLinearB(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeLinearB(d, f,n);
  }
  free(f);
}

double timeunder500QA(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, QuadraticProbing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeQuadraticA(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, QuadraticProbing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500QA(d, f, n);
       }
         x = t / (log(n));
         y = t / n;
         z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printQuadraticTableA(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Quadratic hashing with hash function A \n");
  f = checkDictionaryQuadraticA(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeQuadraticA(d, f,n);
  }
  free(f);
}

double timeunder500QB(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, QuadraticProbing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeQuadraticB(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, QuadraticProbing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500QB(d, f, n);
      }
      x = t / (log(n));
      y = t / n;
      z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printQuadraticTableB(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Quadratic hashing with hash function B \n");
  f = checkDictionaryQuadraticB(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeQuadraticB(d, f,n);
  }
  free(f);
}

double timeunder500DA(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, DoubleHashing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeDoubleA(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashA, DoubleHashing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500DA(d, f, n);
      }
      x = t / (log(n));
      y = t / n;
      z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printDoubleA(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Double hashing with hash function A \n");
  f = checkDictionaryDoubleHashingA(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeDoubleA(d, f,n);
  }
  free(f);
}

double timeunder500DB(closed_dictionary d, closed_table f,int n){
    int collisions=0;
    double ta, tb, t1, t2, t;
    int i, j;
    int k = 100;

    ta = microseconds();
    for (i = 0; i<=k; i++){
      for(j = 0; j < n; j++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, DoubleHashing);
      }
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    for (j = 0; j<=k; j++){
      init_seed();
    }
    tb = microseconds();
    t2 = tb - ta;
    t = (t1 - t2)/k;
    return t;
}

void timeDoubleB(closed_dictionary d, closed_table f,int n){
  double t1, t2, t, x, y, z;
  int i;
  int collisions=0;
  char ast = ' ';

      t1 = microseconds();
      for(i = 0; i < n; i++){
        find_closed(d[rand() % 19062].key, f, 38197, &collisions, hashB, DoubleHashing);
      }
      t2= microseconds();
      t = t2-t1;
      if (t<500){
         ast = '*';
         t = timeunder500DB(d, f, n);
      }
      x = t / (log(n));
      y = t / n;
      z = t / (n*log(n));
      printf("%12d%15.5f%c%15.7f%15.7f%15.7f\n\n", n, t, ast, x, y, z);
}

void printDoubleB(closed_dictionary d){
  int n;
  int totalcollisionsinsertion = 0;
  closed_table f = malloc (38197 * sizeof(entry));
  printf("***Double hashing with hash function B \n");
  f = checkDictionaryDoubleHashingB(d, &totalcollisionsinsertion);
  printf("Inserting 19062 elements... Total number of collisions: %d\n",totalcollisionsinsertion);
  printf("Finding n elements...\n");
  tableHeader();
  for(n = 125; n <= 16000; n*=2){
    timeDoubleB(d, f,n);
  }
  free(f);
}

int main(){
  int totalcollisionsinsertion = 0;
  closed_dictionary d = malloc (19062 * sizeof(item));
  /***********************************EXERCISE 1*****************************/
  CheckLinear();
  CheckQuadratic();
  CheckDouble();
  /***********************************EXERCISE 2*****************************/
    read_synonyms(d);
    free(checkDictionaryLinearA(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Linear Hashing A: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion=0;
    free(checkDictionaryQuadraticA(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Quadratic Hashing A: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion=0;
    free(checkDictionaryDoubleHashingA(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Double Hashing A: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion=0;
    free(checkDictionaryLinearB(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Linear Hashing B: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion = 0;
    free(checkDictionaryQuadraticB(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Quadratic Hashing B: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion = 0;
    free(checkDictionaryDoubleHashingB(d, &totalcollisionsinsertion));
    printf("Total collisions inserting with Double Hashing B: %d\n", totalcollisionsinsertion);
    totalcollisionsinsertion = 0;
    /*********************************EXERCISE 3*****************************/
    init_seed();
    printLinearTableA(d);
    printLinearTableB(d);
    printQuadraticTableA(d);
    printQuadraticTableB(d);
    printDoubleA(d);
    printDoubleB(d);
    free(d);
}
