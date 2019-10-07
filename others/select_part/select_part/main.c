#include <stdio.h>
#include <stdlib.h>
#include "select.h"


int random(int n)//produce [0,n)
{
    return rand()%n;
}
/*int array[61]={53 , 53 , 11 , 53 , 47 , 22 , 81 , 3  , 70 , 26 ,
           54 , 26 , 85 , 45 , 57 , 47 , 11 , 68 , 36 , 27 ,
           6  , 25 , 34 , 60 , 1  , 29 , 86 , 63 , 89 , 86 ,
           56 , 84 , 76 , 34 , 19 , 94 , 46 , 88 , 70 , 59 ,
           52 , 9  , 18 , 14 , 10 , 80 , 43 , 51 , 83 , 90 ,
           35 , 31 , 0  , 21 , 88 , 65 , 53 , 66 , 30 , 43 ,
           39};*/
int main()
{
    srand((unsigned)time(NULL));

    int array[100];
    int num=99;//random(99);

    for(int i=0;i<num;i++)
    {
        array[i]=random(100);
        printf("%d  ",array[i]);
    }
    printf("\n");

    int paiming=random(99);
    int n=select_part(array,num,paiming);

    printf("paiming=  %d  \n  num=%d\n",paiming,n);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
