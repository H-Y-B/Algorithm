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

    int num=10;//random(99);

    int *array=(int*)calloc(num,sizeof(int));
    int *id =(int*)calloc(num,sizeof(int));

    for(int i=0;i<num;i++)
    {
        array[i]=random(100);
        id[i] =i;
        printf("%d:   %d\n",id[i],array[i]);

    }

    insert(array,id,num);

    for(int i=num-1;i>=0;i--)
    {
        printf("%d:   %d\n",id[i],array[i]);
    }

    return 0;
}
