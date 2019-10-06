#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*�󣺸���0
  �ң���*/
void separate_0(int array[],int num){

    int left=0;
    int right=num-1;

    while(left<right){

        //�����һ���������
        while(array[left]<=0&& left<right){
            left++;
        }
        //�ұ���һ��С�ڵ������
        while(array[right]>0 && left<right){
            right--;
        }

        //����
        if(left<right){
            int temp=array[left];
            array[left]=array[right];
            array[right]=temp;
        }

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
        array[i]=random(100)-50;
        //printf("%d:   %d\n",i,array[i]);

    }

    separate_0(array,num);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
