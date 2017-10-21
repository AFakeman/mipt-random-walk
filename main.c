#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Random(unsigned* seed, double p) {
  return (rand_r(seed) / (p * RAND_MAX)) >= 1;
}

int main(int argc, char* argv[]) {
  int a, b, x;
  size_t P, N, i, total_lifetime, reached_b;
  double p, run_time, avg_lifetime, b_probability;
  FILE* stats;
  assert(argc == 7);
  // Lazy input correctness checking.
  assert(sscanf(argv[1], "%d", &a));
  assert(sscanf(argv[2], "%d", &b));
  assert(sscanf(argv[3], "%d", &x));
  assert(sscanf(argv[4], "%lu", &N));
  assert(sscanf(argv[5], "%lf", &p));
  assert(sscanf(argv[6], "%lu", &P));

  run_time = omp_get_wtime();
  total_lifetime = 0;
  reached_b = 0;

#pragma omp parallel for reduction(+ : total_lifetime, reached_b)
  for (i = 0; i < N; i++) {
    size_t lifetime = 0;
    // Using time() as a seed is a bad idea
    // because it is very likely to be same
    // for every thread.
    unsigned random_seed = clock();
    int pos = x;
    while (pos > a && pos < b) {
      if (Random(&random_seed, p))
        pos += 1;
      else
        pos -= 1;
      ++lifetime;
    }
    if (pos == b)
      reached_b += 1;
    total_lifetime += lifetime;
  }
  printf("%ld\n", total_lifetime);
  run_time = omp_get_wtime() - run_time;
  b_probability = reached_b / ((double)N);
  avg_lifetime = total_lifetime / ((double)N);
  stats = fopen("stats.txt", "w");
  fprintf(stats, "%lf %lf %lfs %d %d %d %lu %lf %lu\n", b_probability,
          avg_lifetime, run_time, a, b, x, N, p, P);
  fclose(stats);
}