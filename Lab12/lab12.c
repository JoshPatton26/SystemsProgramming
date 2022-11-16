/* 
  Simple Pthread Program to find the sum of a vector.
  Uses mutex locks to update the global sum. 
  Author: Purushotham Bangalore
  Date: Jan 25, 2009

  To Compile: gcc -O -Wall pthread_psum.c -lpthread
  To Run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct Values{
  double *a, sum;
  int    N, size;
  int tid;
}values;

void *compute(void *arg) {
    int myStart, myEnd, myN, i;
    values *value = (values*)arg;

    // determine start and end of computation for the current thread
    myN = value->N/value->size;
    myStart = value->tid*myN;
    myEnd = myStart + myN;
    int tid=value->tid;
    int size= value->size;
    if (tid == (size-1)) myEnd = value->N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++)
      mysum += value->a[i];

    // grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);
    value->sum = mysum;
    pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {
    long i = 0;
    int j;
    values value[atoi(argv[2])];
    pthread_t *tid;

    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    int N = atoi(argv[1]);
    int size = atoi(argv[2]);
    tid = (pthread_t *)malloc(sizeof(pthread_t)*value[0].size);

    for (j =0; j < size; j++){
      value[j].a = (double *)malloc(sizeof(double)*N);
      value[j].N = atoi(argv[1]); // no. of elements
      value[j].size = atoi(argv[2]); // no. of threads
        for (i=0; i<N; i++){
          value[j].a[i] = (double)(i + 1);
        }
    }

    // create threads
    for ( i = 0; i < size; i++){
      value[i].tid = i;
      pthread_create(&tid[i], NULL, compute, (void *) &value[i]);
    }
    // wait for them to complete
    for ( i = 0; i < value[i].size; i++)
      pthread_join(tid[i], NULL);

    // Add all the partial sums to get a total sum.
    double totalsum = 0.0;
    for (i =0 ; i < size; i ++){
      totalsum += value[i].sum;
    }
    
    fflush(stdout);
    printf("The total is %f, it should be equal to %g\n", 
           totalsum, ((double)N*(N+1))/2);
    
    return 0;
}