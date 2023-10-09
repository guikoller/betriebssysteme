#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i;
  double sum = 0.0;

  for (i=0; i<100000000; i++) {
   //  printf("%d  %lf\n", i, sum);
   sum = sum + (double) i;
  }
  exit(0);
}
