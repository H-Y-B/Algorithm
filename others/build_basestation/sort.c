#include <stdio.h>
#include <stdlib.h>

//From small to large
//insert sort
void insert(int array[],int num) //0 1 2 3... num-1
{
    for(int i=1;i<num;i++)
    {
       int temp=array[i];//the element that needs to insert


       //ͨ�� "˳�����"  ���ҵ� ����λ��
       int j=i;
       for(;j>0;j--)
       {
           if(array[j-1]>temp)
            array[j]=array[j-1];
           else
            break;        //a[j-1]��  ��������  ��һ��С�ڵ���temp=a[i]
       }


       array[j]=temp;
    }
}

