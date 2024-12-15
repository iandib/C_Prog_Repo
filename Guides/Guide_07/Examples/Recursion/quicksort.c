#include <stdio.h>

#define NUMEL(a) (sizeof(a)/sizeof((a)[0]))

void print_array(const int v[], int len);

void qsort1(int v[], int left, int right);
void swap(int v[], int i, int j);


int main(void)
{
	int arr[] = {4, 63, 12, 40, 60, 23, 67, 8, 50, 7, 5, 44};

	print_array(arr, NUMEL(arr));
    qsort1(arr, 0, 11);
	print_array(arr, NUMEL(arr));

    return 0;
}

void print_array(const int v[], int len)
{
	int i;
	for (i=0 ; i<len ; i++)
	{
		printf("%3d", v[i]);
	}
	putchar('\n');
}

/* funcion recursiva quicksort */
/* para ordenar el arreglo en orden ascendente */
/* qsort:  sort v[left]...v[right] into increasing order */
void qsort1(int v[], int left, int right)
{
  int i, last;

  if (left >= right) /* no hace nada si el arreglo contiene */
    return;          /* menos de dos elementos */
  swap(v, left, (left + right)/2); /* mueve el elemento de particion */
  last = left;                     /* a v[0] */
  for (i = left + 1; i <= right; i++)  /* particion */
    if (v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);            /* regresa el elemento de particion */
  qsort1(v, left, last-1);
  qsort1(v, last+1, right);
}

/*funcion swap */
/* para intercambiar los valores de dos elementos*/
/* swap:  interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
