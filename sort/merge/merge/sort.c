#include <stdio.h>
#include <stdlib.h>


void merge_sort(int array[],int left,int right){

    if(left>=right){//只有一个元素

    }else{
        int mid=(right+left)/2;

        //切分
        merge_sort(array,left,mid);
        merge_sort(array,mid+1,right);

        //归并
        merge(array,left,mid,right);
    }
}

//归并
int merge(int array[],int left,int mid,int right){
/*
    merge [left,mid] and [mid+1,right]
*/
    int start=left;
    int num=right-left+1;
    int *temp=(int*)calloc(num,sizeof(int));

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
