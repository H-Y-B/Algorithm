#include <stdio.h>
#include <stdlib.h>

int check_process(int start[],int end[],int num,int test[])
{
    int point=0;

    test[point]=end[0];

    for(int i=1;i<num;i++)
    {
        if(start[i]<=test[point] && test[point]<=end[i])
            continue;
        else
        {
            point++;
            test[point]=end[i];
        }
    }

    return point;

}
