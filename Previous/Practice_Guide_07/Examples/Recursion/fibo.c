#include <stdio.h>

int Fib(int n);
int fibo(int n);

int main(void)
{
    int n=11;
    printf("Fibonacci(%d) = %d\n", n, Fib(n));
	printf("Fibonacci(%d) = %d\n", n, fibo(n));
    return 0;
}

int Fib(int n)
{
  int n2=0, n1=1, rta;
  int i;
  if (n <= 0)
    rta = n2;
  else if (n == 1)
    rta = n1;
  else
    for(i=2 ; i<=n ; i++)
    {
      rta = n1+n2;
      n2=n1;
      n1=rta;
    }
  return rta;
}

int fibo(int n)
{
  if (n <= 1)
    return(n);
  else
    return (fibo(n-1)+fibo(n-2));
}
