#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "check_process.h"


int random(int n)//produce [0,n)
{
    return rand()%n;
}

int main()
{
    srand((unsigned)time(NULL));

    int num=10;//random(99);

    int *start=(int*)calloc(num,sizeof(int));
    int *end=(int*)calloc(num,sizeof(int));

    for(int i=0;i<num;i++)
    {
        end[i]=random(100);
    }
    insert(end,num);

    for(int i=0;i<num;i++)
    {
        start[i]=end[i]-random(100);
    }

    int test[100];
    int point=check_process(start,end,num,test);


    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",start[i],end[i]);
    }

    printf("\n");

    for(int i=0;i<=point;i++)
    {
        printf("%d\n",test[i]);
    }

    return 0;
}
