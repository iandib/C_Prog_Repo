/*******************************
 CallBack Example
 Using qsort() function
*******************************/
#include <stdlib.h>
#include <stdio.h>


#define SIZEL(v) sizeof(*(v))
#define NUMEL(v) (sizeof(v)/SIZEL(v))


int asc (const void *pa, const void *pb);
int desc (const void *pa, const void *pb);
void print_array (int arr[],int size,const char* type);


/********************************************************************/

int main(void)
{
    int arr [] ={10,9,8,1,2,3,5};
    
    print_array(arr, NUMEL(arr), "Original Order");

    /*  sort in ascending order  */ 
    qsort(arr, NUMEL(arr), SIZEL(arr), asc);
    print_array(arr, NUMEL(arr), "Ascending Order");


    /*  sort in descending order  */ 
    qsort(arr, NUMEL(arr), SIZEL(arr), &desc);
    print_array(arr, NUMEL(arr), "Descending Order");

    return 0;
}



/*  callback  */ 
int asc (const  void *pa, const void *pb) 
{ 
    return ( *(int*)pa - *(int*)pb ); 
} 


/*  callback  */ 
int desc (const void *pa, const void *pb) 
{ 
    return ( *(int*)pb - *(int*)pa ); 
} 


/* This function prints the array elements */
void print_array (int arr[], int size, const char* type)
{
    int i;

    printf("Arr:(%s)", type);

    for (i=0;i<size;i++)
    {
        printf(" %d",arr[i]);
    }
    printf("\n");
}


