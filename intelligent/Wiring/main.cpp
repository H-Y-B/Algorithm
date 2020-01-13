#include <iostream>
#include <queue>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

using namespace std;

struct Position{
    int row;
    int col;
};

bool FindPath(Position start,
              Position finish,
              int& PathLen,
              Position *&path,
              int **grid,
              int m,
              int n
              ){

    cout<<"进入FindPath"<<endl;

    if((start.row==finish.row)&&(start.col==finish.col))
    {
        PathLen=0;
        return true;
    }

    Position offset[4];
    offset[0].row=0; offset[1].row=1; offset[2].row=0;  offset[3].row=-1;
    offset[0].col=1; offset[1].col=0; offset[2].col=-1; offset[3].col=0;

    int NumNeighBlo=4;
    Position here,nbr;
    here.row=start.row;
    here.col=start.col;

    grid[start.row][start.col]=0;

    queue<Position> q_FindPath;

    do{

        int num=0;

        Position selectPosition[5];

        for(int i=0;i<NumNeighBlo;i++)//遍历here周围的四个点
        {
            nbr.row=here.row + offset[i].row;
            nbr.col=here.col + offset[i].col;

            if(grid[nbr.row][nbr.col]==-1)//如果有路
            {
                grid[nbr.row][nbr.col]=grid[here.row][here.col] + 1;//路径由 0、1、2、3....来标记

                if(nbr.row==finish.row && nbr.col==finish.col)
                    break;

                selectPosition[num].row=nbr.row;
                selectPosition[num].col=nbr.col;
                num++;
            }
        }

        if(num>0)//如果here周围有点可以走
            q_FindPath.push(selectPosition[rand()%num]);

        //成功
        if(nbr.row==finish.row && nbr.col==finish.col)
            break;

        //失败
        if(q_FindPath.empty())
            return false;

        here=q_FindPath.front();

        q_FindPath.pop();

    }while(true);


    PathLen=grid[finish.row][finish.col];
    path=new Position[PathLen];

    here=finish;

    for(int j=PathLen-1;j>=0;j--)
    {
        path[j]=here;
        for(int i=0;i<NumNeighBlo;i++)
        {
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;

            if(grid[nbr.row][nbr.col]==j)
                break;
        }
        here=nbr;
    }

    return true;
}


int main()
{
    cout << "------分支限界法之布线问题" << endl;

    int path_len,path_len1;

    int m,n;

    Position *path;
    Position *path1;

    Position start,finish;
    Position start1,finish1;

    cout<<"在一个m*n的棋盘上，请分别输入m和n，代表行数和列数，然后输入回车"<<endl;

    cin>>m>>n;

    int **grid = new int*[m+2];
    int **grid1= new int*[m+2];

    for(int i=0;i<m+2;i++)
    {
        grid[i]=new int[n+2];
        grid1[i]=new int[n+2];
    }

    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            grid[i][j]=-1;
        }
    }

    for(int i=0;i<=n+1;i++)
        grid[0][i]=grid[m+1][i]=-2;
    for(int i=0;i<=m+1;i++)
        grid[i][0]=grid[i][n+1]=-2;

    cout<<"初始化棋盘格和加围墙"<<endl;
    cout<<"----------------------------------"<<endl;

    for(int i=0;i<m+2;i++)
    {
        for(int j=0;j<n+2;j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"----------------------------------"<<endl;

    cout<<"请输入已经占据的位置 行坐标 列坐标，代表此位置不能布线"<<endl;

    while(true)
    {
        int ci,cj;
        cin>>ci>>cj;
        if(ci>m||cj>n)
        {
            cout<<"输入非法";
            continue;
        }
        else if(ci==0||cj==0)
            break;
        else
            grid[ci][cj]=-3;
    }

    //布线前的棋盘格
    cout<<"布线前的棋盘格"<<endl;
    cout<<"------------------------------"<<endl;
    for(int i=0;i<m+2;i++)
    {
        for(int j=0;j<n+2;j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"------------------------------"<<endl;


    cout<<"请输入起点位置坐标"<<endl;
    cin>>start.row>>start.col;
    cout<<"请输入终点位置坐标"<<endl;
    cin>>finish.row>>finish.col;

    cout<<"即将进入FindPath  1"<<endl;

    DWORD startTime,stopTime;
    srand((unsigned)time(NULL));
    int time=0;
    start1  =start;
    finish1 =finish;

    path_len1=path_len;
    path1    =NULL;

    for(int i=0;i<m+2;i++)
    {

        for(int j=0;j<n+2;j++){
            //cout<<i<<" "<<j<<endl;
            grid1[i][j]=grid[i][j];
        }
    }

    bool result =FindPath(start1,finish1,path_len1,path1,grid1,m,n);

    while(result==false && time<200)
    {
        start1=start;
        finish1=finish;
        path_len1=path_len;
        path1=NULL;
        for(int i=0;i<m+2;i++)
        {
            for(int j=0;j<n+2;j++)
                grid1[i][j]=grid[i][j];
        }

        time++;
        cout<<endl;
        cout<<"没有找到路线，第"<<time<<"次失败"<<endl;
        result=FindPath(start1,finish1,path_len1,path1,grid1,m,n);
    }

    stopTime=GetTickCount();

    if(result){
        cout<<"----------------------------"<<endl;
        cout<<"$ 代表围墙"<<endl;
        cout<<"# 代表已经占据的点"<<endl;
        cout<<"* 代表布线路线"<<endl;
        cout<<"= 代表还没有布线的点"<<endl;
        cout<<"----------------------------"<<endl;

        for(int i=0;i<=m+1;i++)
        {
            for(int j=0;j<=n+1;j++)
            {
                if(grid1[i][j]==-2)
                    cout<<"$ ";
                else if(grid1[i][j]==-3)
                    cout<<"# ";
                else{
                    int r;
                    for(r=0;r<path_len1;r++)
                    {
                        if(i==path1[r].row && j==path1[r].col)
                        {
                            cout<<"* ";
                            break;
                        }

                        if(i==start1.row && j==start1.col)
                        {
                            cout<<"* ";
                            break;
                        }
                    }
                    if(r==path_len1)
                        cout<<"= ";
                }
            }
            cout<<endl;
        }
        cout<<"-------------------------------------------"<<endl;
        cout<<"路径坐标和长度"<<endl;
        cout<<""<<endl;

        cout<<"("<<start1.row<<","<<start1.col<<")"<<" ";
        for(int i=0;i<path_len1;i++)
        {
            cout<<"("<<path1[i].row<<","<<path1[i].col<<")"<<" ";
        }
        cout<<endl;
        cout<<endl;
        cout<<"路径长度："<<path_len1+1<<endl;
        cout<<endl;
        time++;
        cout<<"布线完毕，查找"<<time<<"次"<<endl;
        printf("运行时间: %11d ms\n",stopTime-startTime);



    }
    else{

        cout<<endl;
        cout<<"经过多次尝试，仍然没有找到路线"<<endl;
    }
    system("pause");
    return 0;
}



















