#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include <time.h>

int random(int n)//produce [0,n)
{
    return rand()%n;
}

int main()
{
    srand((unsigned)time(NULL));

    int num=random(99);

    int *array=(int*)calloc(num,sizeof(int));

    for(int i=0;i<num;i++)
    {
        array[i]=random(100);
        //printf("%d:   %d\n",i,array[i]);
    }

    insert_bi(array,num);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
