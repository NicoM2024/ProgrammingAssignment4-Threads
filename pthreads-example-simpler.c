//--------------------------------------------------------
// jdh CS 3010 Fall 2026
// - simple example of pthreads
// - this program looks for the maximum value in an array;
// - each thread looks at a different region of the array
//--------------------------------------------------------

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 2
#define NUM_ELEMENTS 1000

void *runner(void *param);

typedef struct {
  int startIndex;
  int endIndex;
  int maxVal;
} ThreadInfo;

int values[NUM_ELEMENTS];

//---------------------------------------------------------------------------

void *runner(void *param) {
  ThreadInfo *data;
  int i, maxVal;

  data = (ThreadInfo *) param;
  printf("I am runner; will do max for the range %d to %d\n",
          data->startIndex, data->endIndex);

  maxVal = values[data->startIndex];

  for (i=data->startIndex; i<=data->endIndex; ++i) {
    if (values[i] > maxVal)
      maxVal = values[i];
  }

  data->maxVal = maxVal;
  printf("my max is %d\n", data->maxVal);
  pthread_exit(NULL);
} // runner()

//---------------------------------------------------------------------------

int main() {
  ThreadInfo tdata[NUM_THREADS]; // holds data we want to give to each thread
  pthread_t tids[NUM_THREADS];    // thread identifier for child thread #1
  int maxVal;
  int i, pos, chunkSize;

  // initialize the array with random integers in the range 0..NUM_ELEMENTS
#ifdef WIN32
    for (i=0; i<NUM_ELEMENTS; ++i) {
        values[i] = (int) ((float) rand() / (RAND_MAX + 1.0));
    }
#else
    for (i=0; i<NUM_ELEMENTS; ++i) {
        values[i] = (int) NUM_ELEMENTS * drand48();
    }
#endif

  // set up bounds for the threads
  chunkSize = NUM_ELEMENTS / NUM_THREADS;
  pos = 0;
  for (i=0; i<NUM_THREADS; ++i) {
    tdata[i].startIndex = pos;
    tdata[i].endIndex = tdata[i].startIndex + chunkSize;
    pos = pos + chunkSize + 1;
  }

  // adjust last region if necessary
  if (tdata[NUM_THREADS-1].endIndex < NUM_ELEMENTS-1)
    tdata[NUM_THREADS-1].endIndex = NUM_ELEMENTS - 1;
  else if (tdata[NUM_THREADS-1].endIndex > NUM_ELEMENTS-1)
    tdata[NUM_THREADS-1].endIndex = NUM_ELEMENTS - 1;

  // create child threads
  for (i=0; i<NUM_THREADS; ++i)
    pthread_create(&tids[i], NULL, runner, &tdata[i]);

  // wait for the child threads to terminate
  for (i=0; i<NUM_THREADS; ++i)
    pthread_join(tids[i], NULL);

  // gather data from the individual results
  maxVal = tdata[0].maxVal;
  for (i=1; i<NUM_THREADS; ++i) {
    if (tdata[i].maxVal > maxVal)
      maxVal = tdata[i].maxVal;
  }

  printf("overall max is %d\n", maxVal);
  return 0;
} // main()
