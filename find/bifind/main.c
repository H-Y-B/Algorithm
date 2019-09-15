#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

int bifind(int array[],int num,int left,int right)
{
  while(left<=right)
  {
      int mid=(right+left)/2;

      if(array[mid]==num)
          return mid;
      else if(array[mid]<num)
          left=mid+1;
      else
          right=mid-1;
  }
  return -1;
}

int main()
{
    srand((unsigned)time(NULL));

    int num=random(50);

    int *array=(int*)calloc(num,sizeof(int));

    for(int i=0;i<num;i++)
        array[i]=random(50);

    insert(array,num);//sort ascending


//    for(int i=0; i<num; i++)
//        printf("%d ",array[i]);
//    printf("\n%d\n",num);

    int result=bifind(array,num,0,num-1);
    if(result==-1)
    {
        printf("no");
    }
    else
    {
        printf("in %d",result);
    }

    return 0;
}
