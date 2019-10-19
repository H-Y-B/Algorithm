#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "build_basestation.h"

int random(int n)//produce [0,n)
{
    return rand()%n;
}

int main()
{
    srand((unsigned)time(NULL));

    int num=10;//random(99);

    int *array=(int*)calloc(num,sizeof(int));

    for(int i=0;i<num;i++)
    {
        array[i]=random(100000);
    }

    insert(array,num);





    int build[10];
    int build_num=build_basestation(array,num,build);




    for(int i=0;i<num;i++)
    {
        printf("%d  ",array[i]);
    }
    printf("\n");
    for(int i=0;i<build_num;i++)
    {
        printf("%d  ",build[i]);
    }


    return 0;
}
