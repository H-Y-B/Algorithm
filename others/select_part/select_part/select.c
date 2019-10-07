#include <stdio.h>
#include <stdlib.h>



int part(int array[],int left,int right){

    int i=left+1,j=right;

    int x=array[left];

    while(1)
    {
        while(array[i]<=x && i<=right  )i++;  //“<=x” 这里的“=”是需要的，
                                               //否则在 数组中有多个x值的情况下，会造成死循环
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



int select_part(int array[],int num,int paiming){//paiming:  0、1、2......n-1

    int left=0,right=num-1;

    while(1)
    {
        int mid=part(array, left, right);

        if(mid<paiming){
            left=mid+1;
        }else if(mid>paiming){
            right=mid-1;
        }else{
            return array[mid];
        }
    }



}
