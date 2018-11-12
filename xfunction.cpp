#include <sys/time.h>
#include <stdlib.h>
#include "include.hh"

int			xrandom(int i)
{
  struct timeval	usec;

  gettimeofday(&usec, NULL);
  srand((long int)usec.tv_usec);
  return (random() % i);
}
