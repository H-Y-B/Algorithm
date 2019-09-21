#include <stdio.h>
#include <stdlib.h>

int array[100];

void merge_sort(int left,int right){

    if(left>=right){//只有一个元素

    }else{
        int mid=(right+left)/2;

        merge_sort(left,mid);
        merge_sort(mid+1,right);

        merge(left,mid,right);
    }
}

int merge(int left,int mid,int right){
/*
    merge [left,mid] and [mid+1,right]
*/
    int start=left;
    int num=right-left+1;
    int *temp=(int*)calloc(num,sizeof(int));

    int num_left=mid-left+1;
    int num_right=right-(mid+1)+1;

    int n=0;
    int a1=left,a2=mid+1;
    while(a1<=mid && a2<=right){
        temp[n++]=array[a1]<array[a2]? array[a1++]:array[a2++];
    }


    if(a1<=mid){
        for(;n<num;n++)
            temp[n]=array[a1++];
    }else if(a2<=right){
        for(;n<num;n++)
            temp[n]=array[a2++];
    }


    for(n=0;n<num;n++)
    {
        array[start++]=temp[n];
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

    for(int i=0;i<num;i++)
    {
        array[i]=random(100);
        printf("%d\n",array[i]);

    }

    merge_sort(0,num-1);

    for(int i=0;i<num;i++)
    {
        printf("%d:   %d\n",i,array[i]);
    }

    return 0;
}
