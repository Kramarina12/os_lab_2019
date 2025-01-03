#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>
#include <sys/time.h>

#include "sum.h"
#include "../../lab3/src/utils.h"

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;

  static struct option options[] = {{"threads_num", required_argument, 0, 0},
                                    {"seed", required_argument, 0, 0},
                                    {"array_size", required_argument, 0, 0},
                                    {0, 0, 0, 0}};

  int option_index = 0;
  int c;

  while ((c = getopt_long(argc, argv, "", options, &option_index)) != -1) {
    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            threads_num = atoi(optarg);
            if (threads_num <= 0)
            {
              printf("Invalid input: threads_num must be a positive number\n");
              return 1;
            }
            break;
          case 1:
            seed = atoi(optarg);
            if (seed <= 0)
            {
              printf("Invalid input: seed must be a positive number\n");
              return 1;
            }
            break;
          case 2:
            array_size = atoi(optarg);
            if (array_size <= 0)
            {
              printf("Invalid input: array_size must be a positive number\n");
              return 1;
            }
            break;
          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (threads_num == 0 || array_size == 0 || seed == 0) {
    printf("Usage: %s --threads_num \"num\" --seed \"num\" --array_size \"num\"\n", argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

  pthread_t threads[threads_num];
  struct SumArgs args[threads_num];

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (uint32_t i = 0; i < threads_num; i++) {
    args[i].array = array;
    args[i].begin = i * (array_size / threads_num);
    args[i].end = (i + 1) * (array_size / threads_num);
    if (i == threads_num - 1) {
      args[i].end = array_size;
    }
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  gettimeofday(&end, NULL);
  double elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %f ms\n", elapsed_time);
  return 0;
}
