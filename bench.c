// bench.c
// execute a large number of calls to functions getmem and freemem
// to allocate and free blocks of random sizes and in random order

// CSE374 HW6
// Yirou Luo
// Mar 2, 2017

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"

#define NTRIALS 10000
#define PCTGET 50
#define PCTLARGE 10
#define SMALL_LIMIT 200
#define LARGE_LIMIT 20000

// Report the current status in format, including:
// Total CPU time used; total amount of storage acquired;
// Total number of free blocks; average number of bytes of free blocks
void report(int percent, double cpu_time, uintptr_t total_size,
            uintptr_t total_free, uintptr_t n_free_blocks);

int main(int argc, char* argv[]) {
  clock_t start, end;
  double cpu_time;
  start = clock();
  // initialize all parameters
  int ntrials, pctget, pctlarge, small_limit, large_limit, random_seed;
  if (argc > 1) {
    if (argv[1] <= 0) {
      printf("ntrials must be positive.\n");
      return 1;
    }
    ntrials = atoi(argv[1]);
  } else {
    ntrials = NTRIALS;
  }

  if (argc > 2) {
    pctget = atoi(argv[2]);
    if (pctget > 100 || pctget < 0) {
      printf("pctget should be between 0 and 100.\n");
      return 1;
    }
  } else {
    pctget = PCTGET;
  }

  if (argc > 3) {
    pctlarge = atoi(argv[3]);
    if (pctlarge > 100 || pctlarge < 0) {
      printf("pctlarge should be between 0 and 100.\n");
      return 1;
    }
  } else {
    pctlarge = PCTLARGE;
  }

  if (argc > 4) {
    small_limit = atoi(argv[4]);
    if (small_limit <= 0) {
      printf("small_limit must be positive.\n");
      return 1;
    }
  } else {
    small_limit = SMALL_LIMIT;
  }

  if (argc > 5) {
    large_limit = atoi(argv[5]);
    if (large_limit <= 0) {
      printf("large_limit must be positive.\n");
      return 1;
    } else if (small_limit >= large_limit) {
      printf("The small_limit must be less than large_limit.\n");
      return 1;
    }
  } else {
    large_limit = LARGE_LIMIT;
  }

  if (argc > 6) {
    random_seed = atoi(argv[6]);
  } else {
    random_seed = time(NULL);
  }

  srand(random_seed);

  // the array to store all the (void *) returned by getmem function
  void ** getmempt;
  getmempt = (void **) malloc(ntrials * sizeof(void *));

  // create three pointers to get access to the global variables
  uintptr_t total_size;
  uintptr_t total_free;
  uintptr_t n_free_blocks;


  // the count of the number of the pointers returned from getmem function
  int nget = 0;

  // control the time of report
  int tenpct = 1;

  // randomly perform ntrials times memory operations
  for (int i = 0; i < ntrials; i++) {
    int pct = rand() % 100;
    if (pctget > pct) {  // getmem
      uintptr_t bsize;
      if (rand() % 100 < pctlarge) {  // get a large chunk of memory
        bsize = small_limit + rand() % (large_limit - small_limit);
      } else {  // get a small piece
        bsize = 1 + rand() % small_limit;
      }
      getmempt[nget++] = getmem(bsize);
    } else {  // pick up a chunk of memory randomly and free it
      if (nget > 0) {
        int n = rand() % (nget);
        freemem(getmempt[n]);
        getmempt[n] = getmempt[--nget];
      }
    }

    // Report after 10%, 20%, ..., 100%
    if ((i + 1) * 10 / ntrials >= tenpct) {
      end = clock();
      cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      total_free = 0, n_free_blocks = 0;
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      report(tenpct * 10, cpu_time, total_size, total_free, n_free_blocks);
      tenpct++;
    }
  }

  return 0;
}

void report(int percent, double cpu_time, uintptr_t total_size,
            uintptr_t total_free, uintptr_t n_free_blocks) {
  printf("%d percent completed.\n", percent);
  printf("Total CPU time used in seconds:  %f\n", cpu_time);
  printf("Total amount of storage acquired in bytes: %lu\n", total_size);
  printf("Total number of free blocks: %lu\n", n_free_blocks);
  if (n_free_blocks == 0) {
    printf("Average number of bytes of free blocks: 0\n");
  } else {
    printf("Average number of bytes of free blocks: %lu\n",
           total_free / n_free_blocks);
  }
  printf("\n");
  return;
}
