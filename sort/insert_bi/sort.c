#include <stdio.h>
#include <stdlib.h>
/*
    二分法插入排序
    使用“二分查找”找到插入的位置，后移，插入


    可以改进为 二分查找
    & 时间复杂度
    最坏情况：输入序列是逆序的，
              每次的插入位置都在第一个，这就需要 将前面整个有序序列后移
              O（n^2）~ 1+2+3......+n-1

    最好情况：序列本身就是顺序的，不需要“后移”，瓶颈是“查找插入位置”
              O(log1+log2+...+logn)=O(log(n!))=O(nlogn)
*/



/*
    不会因为等于某一个值而停止查找，
    它将查找整个序列直到left<=right条件不满足而得到插入的位置
*/
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
  return left;//返回的插入位置
}


//From small to large
void insert_bi(int array[],int num) //0 1 2 3... num-1
{
    for(int i=1;i<num;i++)
    {
       int temp=array[i];//the element that needs to insert

       //通过 "二分查找"  来找到 插入位置
       int j=bifind(array,temp,0,i-1);

       //后移
       for(int n=i;n>j;n--){
           array[n]=array[n-1];
       }

       //插入
       array[j]=temp;
    }
}


