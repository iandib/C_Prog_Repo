#include <stdio.h>
#include <stdlib.h>

int CompaFun(const void *elem_a, const void *elem_b);
void printArrInt(int arr[], int len);

int main()
{
    int array[]={743, 712, 513, 813, 883, 634};
    int nElems=sizeof(array)/sizeof(int);

    printf("Antes de ordenar:\n");
    printArrInt(array, nElems);

    qsort(array, nElems, sizeof(int), CompaFun);

    printf("Ya ordenado:\n");
    printArrInt(array, nElems);

    return 0;
}


int CompaFun(const void *elem_a, const void *elem_b)
{
    return (*(int*)elem_a) > (*(int*)elem_b);
}


void printArrInt(int arr[], int len)
{
    int i;

    printf("[");
    for(i=0 ; i<len ; i++)
    {
        printf("%8d",arr[i]);
    }
    printf(" ]\n");
}
