#include <stdio.h>
#include <stdlib.h>

int  build_basestation(int array[],int num,int build[]){

    int build_num=0;

    if(num<=1){
        build[0]=array[0];
        build_num++;
        return build_num;
    }

    if(array[num-1]-array[0]<=8000)
    {
        build[0]=(array[num-1]-array[0])/2;
        build_num++;
        return build_num;

    }else{
        int start=array[0];
        int mid  =start+4000;
        int end  =start+8000;
        build[build_num]=mid;
        build_num++;

        for(int i=0;i<num;i++)
        {
            if(array[i]>end)
            {
                start=array[i];
                mid  =start+4000;
                end  =start+8000;
                build[build_num]=mid;
                build_num++;
            }

        }

        return build_num;
    }

}
