#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int random(int n)//produce [0,n)
{
    return rand()%n;
}

int main()
{
    srand((unsigned)time(NULL));

    int array[100];
    int num=random(99);

    for(int i=0;i<num;i++)
    {
        array[i]=random(100);
        //printf("%d\n",array[i]);
    }

    merge_sort(array,0,num-1);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
