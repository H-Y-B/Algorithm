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

    cout<<"����FindPath"<<endl;

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

        for(int i=0;i<NumNeighBlo;i++)//����here��Χ���ĸ���
        {
            nbr.row=here.row + offset[i].row;
            nbr.col=here.col + offset[i].col;

            if(grid[nbr.row][nbr.col]==-1)//�����·
            {
                grid[nbr.row][nbr.col]=grid[here.row][here.col] + 1;//·���� 0��1��2��3....�����

                if(nbr.row==finish.row && nbr.col==finish.col)
                    break;

                selectPosition[num].row=nbr.row;
                selectPosition[num].col=nbr.col;
                num++;
            }
        }

        if(num>0)//���here��Χ�е������
            q_FindPath.push(selectPosition[rand()%num]);

        //�ɹ�
        if(nbr.row==finish.row && nbr.col==finish.col)
            break;

        //ʧ��
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
    cout << "------��֧�޽編֮��������" << endl;

    int path_len,path_len1;

    int m,n;

    Position *path;
    Position *path1;

    Position start,finish;
    Position start1,finish1;

    cout<<"��һ��m*n�������ϣ���ֱ�����m��n������������������Ȼ������س�"<<endl;

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

    cout<<"��ʼ�����̸�ͼ�Χǽ"<<endl;
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

    cout<<"�������Ѿ�ռ�ݵ�λ�� ������ �����꣬�����λ�ò��ܲ���"<<endl;

    while(true)
    {
        int ci,cj;
        cin>>ci>>cj;
        if(ci>m||cj>n)
        {
            cout<<"����Ƿ�";
            continue;
        }
        else if(ci==0||cj==0)
            break;
        else
            grid[ci][cj]=-3;
    }

    //����ǰ�����̸�
    cout<<"����ǰ�����̸�"<<endl;
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


    cout<<"���������λ������"<<endl;
    cin>>start.row>>start.col;
    cout<<"�������յ�λ������"<<endl;
    cin>>finish.row>>finish.col;

    cout<<"��������FindPath  1"<<endl;

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
        cout<<"û���ҵ�·�ߣ���"<<time<<"��ʧ��"<<endl;
        result=FindPath(start1,finish1,path_len1,path1,grid1,m,n);
    }

    stopTime=GetTickCount();

    if(result){
        cout<<"----------------------------"<<endl;
        cout<<"$ ����Χǽ"<<endl;
        cout<<"# �����Ѿ�ռ�ݵĵ�"<<endl;
        cout<<"* ������·��"<<endl;
        cout<<"= ����û�в��ߵĵ�"<<endl;
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
        cout<<"·������ͳ���"<<endl;
        cout<<""<<endl;

        cout<<"("<<start1.row<<","<<start1.col<<")"<<" ";
        for(int i=0;i<path_len1;i++)
        {
            cout<<"("<<path1[i].row<<","<<path1[i].col<<")"<<" ";
        }
        cout<<endl;
        cout<<endl;
        cout<<"·�����ȣ�"<<path_len1+1<<endl;
        cout<<endl;
        time++;
        cout<<"������ϣ�����"<<time<<"��"<<endl;
        printf("����ʱ��: %11d ms\n",stopTime-startTime);



    }
    else{

        cout<<endl;
        cout<<"������γ��ԣ���Ȼû���ҵ�·��"<<endl;
    }
    system("pause");
    return 0;
}



















