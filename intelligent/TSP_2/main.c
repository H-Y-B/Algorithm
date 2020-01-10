#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>


#define nCities 99       //城市数量
#define SPEED 0.98        //退火速度
#define INITIAL_TEMP 1000 //初始温度
#define L 100*nCities     //Markov链的长度
typedef enum __bool { false = 0, true = 1, } bool;

struct unit{
    double length;
    double length_table[nCities+1][nCities+1];
    int path[nCities];
};

//2-OPT交换法生成邻居
void getNewSolution(struct unit* p)
{
    double r1 = ((double)rand())/(RAND_MAX+1.0);
    double r2 = ((double)rand())/(RAND_MAX+1.0);
    int pos1 = (int)(nCities*r1); //第一个交叉点的位置
    int pos2 = (int)(nCities*r2);

    int temp = p->path[pos1];
    p->path[pos1] = p->path[pos2];
    p->path[pos2] = temp;   // 交换两个点
}

//计算路径长度
void CalCulate_length(struct unit *p)
{
    p->length=0;

    for(int i=1;i<nCities;i++)
    {
        p->length= p->length  +  p->length_table[p->path[i-1]][p->path[i]];
    }
    p->length=p->length+p->length_table[nCities-1][0];//回到出发点
}

bool Accept(struct unit* best,struct unit* temp,double t)
{
    if(best->length > temp->length)
        return true;
    else
    {
        int q=(int)(exp((best->length - temp->length)/t)*100);
        int r=rand()%101;
        if(q>r)
            return true;
    }
    return false;
}

//初始化函数, 初始化一个解
void generate(struct unit *temp)
{
    //随机生成 城市间的距离
    for(int i=1;i<=nCities;i++)
    {
        for(int j=1;j<=nCities;j++)
        {
            if(i==j)
                temp->length_table[i][j]=0;
            else
                temp->length_table[i][j]=temp->length_table[j][i]= (double)(rand()%999);
        }
    }

    //初始化一个解
    for(int i=0;i<nCities;i++)
        temp->path[i] = i+1;
}

void SA_TSP(){
    srand(time(NULL));

    double r=0.98;//SPEED;
    double t=INITIAL_TEMP;
    const double t_min=0.001;

    struct unit temp,best;

    generate(&temp);//生成一个新问题，并初始化一个解

    CalCulate_length(&temp);

    memcpy(&best,&temp,sizeof(temp));

    while(t>t_min)
    {
        for(int i=0;i<L;i++)
        {
            getNewSolution(&temp);
            CalCulate_length(&temp);

            if(Accept(&best,&temp,t))
                memcpy(&best,&temp,sizeof(temp));
            else
                memcpy(&temp,&best,sizeof(temp));
        }
        t=t*r;

    }

    printf("最优路径长度为:%f\n",best.length);

    for(int i=0;i<nCities;i++){
        printf("%d-->",best.path[i]);
    }
        printf("%d\n",best.path[0]);

    return;
}

int main()
{
    time_t start,finish;
    start = clock(); // 程序运行开始计时
    SA_TSP();
    finish = clock(); // 退火过程结束

    double duration = ((double)(finish-start))/CLOCKS_PER_SEC; // 计算时间
    printf("程序运行耗时:%lf秒.\n",duration);

    return 0;
}
