#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//From small to large
//insert sort
void insert(int array[],int num) //0 1 2 3... num-1
{
    for(int i=1;i<num;i++)
    {
       int temp=array[i];//the element that needs to insert

       int j=i;
       for(;j>0;j--)
       {
           if(array[j-1]>temp)  //compare from back to front numbers
            array[j]=array[j-1];
           else
            break;
       }
       array[j]=temp;
    }
}

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
    }

    insert(array,num);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
