#include <stdio.h>
#include <stdlib.h>

/*
    ��������
*/

int part(int array[],int left,int right){

    int i=left,j=right+1;

    int x=array[left];//ѡ��mid

    while(1){
        while(array[++i]<x);
        while(array[--j]>x);

        if(i>=j)break;

        //Swap
        int temp=array[j];
        array[j]=array[i];
        array[i]=temp;
    }

    array[left]=array[j];
    array[j]=x;//mid�ŵ�����ȷ��λ����

    return j;
}


void quick_sort(int array[],int left,int right){

    if(left<right){
        int mid=part(array,left,right);
        //һ��Ԫ���ҵ����������ȷλ��

        quick_sort(array,left,mid-1);
        quick_sort(array,mid+1,right);
    }

}
