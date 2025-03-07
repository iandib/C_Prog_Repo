#include <stdio.h>

int main(void)
{
  int a,b,c,d,e;
  int *ap[5];

  e = 1;
  ap[0] = &a;
  *(ap+1) = &b;
  c = 2;
  *(ap+c) = &c;
  ap[c+1] = &d;
  *(ap+4) = &e;
  ap[0] = ap[2];

  return 0;
}

