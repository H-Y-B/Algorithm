#include <stdio.h>
#include <stdlib.h>
/*
  插入排序
  关键操作是："比较"和"后移"

  注意：需要通过 "查找算法" 来找到 插入的位置
        这里的查找算法 一般为 顺序查找
        & 时间复杂度
          1+2+3+4......+n=  n(n-1)2  ~ n^2

        可以改进为 二分查找
*/


//From small to large
//insert sort
void insert(int array[],int num) //0 1 2 3... num-1
{
    for(int i=1;i<num;i++)
    {
       int temp=array[i];//the element that needs to insert


       //通过 "顺序查找"  来找到 插入位置
       int j=i;
       for(;j>0;j--)
       {
           if(array[j-1]>temp)
            array[j]=array[j-1];
           else
            break;        //a[j-1]是  从右往左  第一个小于等于temp=a[i]
       }


       array[j]=temp;
    }
}
