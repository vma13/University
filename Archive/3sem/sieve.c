#include <math.h>
#include <stdlib.h>

#include "sieve.h"

bool *initialize_sieve(int size)
{
  bool *sieve = (bool *) malloc(size*sizeof(int));

  return sieve;
}

void finalize_sieve(bool *sieve)
{
  free(sieve);
}

void build_sieve(bool *sieve, int size)
{
  int i;
  int sqrt_size = floor(sqrt(size));

  for (i = 0; i < size; i++)
    sieve[i] = true;
  sieve[1] = false;
  for (i = 2; i <= sqrt_size; i++) {
    if (sieve[i]) {
      int j;
      for (j = i*i; j < size; j += i)
        sieve[j] = false;
    }
  }
}