#include <stdio.h>
#include <stdlib.h>
/*
    ���ַ���������
    ʹ�á����ֲ��ҡ��ҵ������λ�ã����ƣ�����


    ���ԸĽ�Ϊ ���ֲ���
    & ʱ�临�Ӷ�
    ��������������������ģ�
              ÿ�εĲ���λ�ö��ڵ�һ���������Ҫ ��ǰ�������������к���
              O��n^2��~ 1+2+3......+n-1

    �����������б������˳��ģ�����Ҫ�����ơ���ƿ���ǡ����Ҳ���λ�á�
              O(log1+log2+...+logn)=O(log(n!))=O(nlogn)
*/



/*
    ������Ϊ����ĳһ��ֵ��ֹͣ���ң�
    ����������������ֱ��left<=right������������õ������λ��
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
  return left;//���صĲ���λ��
}


//From small to large
void insert_bi(int array[],int num) //0 1 2 3... num-1
{
    for(int i=1;i<num;i++)
    {
       int temp=array[i];//the element that needs to insert

       //ͨ�� "���ֲ���"  ���ҵ� ����λ��
       int j=bifind(array,temp,0,i-1);

       //����
       for(int n=i;n>j;n--){
           array[n]=array[n-1];
       }

       //����
       array[j]=temp;
    }
}


