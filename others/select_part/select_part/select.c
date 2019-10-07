#include <stdio.h>
#include <stdlib.h>


/*����ÿ�ζ�ѡ�� array[left] ��part
   ����ͨ���ı� x ��ѡ�񷽷������Ľ��㷨��*/
int part(int array[],int left,int right){

    int i=left+1,j=right;

    int x=array[left];

    while(1)
    {
        while(array[i]<=x && i<=right  )i++;  //��<=x�� ����ġ�=������Ҫ�ģ�
                                               //������ �������ж��xֵ������£��������ѭ��
        while(array[j]>x && j>=left+1  )j--;

        if(i>j) break;

        //Swap
        int temp = array[i];
        array[i]=array[j];
        array[j]=temp;
    }

    array[left]=array[j];
    array[j]=x;
    return j;
}

/* ѡ��
        ����Ŀ��������˼�룬
        ��part���ҳ�һ������������
        Ȼ�󣬱Ƚ�
        ����part �������������ڵ�����*/
int select_part(int array[],int num,int paiming){//paiming:  0��1��2......n-1

    int left=0,right=num-1;

    while(1)
    {
        int mid=part(array, left, right);//���ҵ�array[left]������
                                         //��ʱarray[left]�Ѿ�������������������ȷλ���ϡ�
        if(mid<paiming){
            left=mid+1;
        }else if(mid>paiming){
            right=mid-1;
        }else{
            return array[mid]; //һ����return
        }
    }
}
