#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define popsize 200   //种群的规模
#define pc      0.618 //交配概率
#define pm      0.03  //变异概率
#define lchrom  90    //染色体长度
#define maxgen  1000  //最大进化代数
typedef enum __bool { false = 0, true = 1, } bool;

struct population{
    unsigned int chrom[lchrom];//染色体
    double weight;          //背包重量
    double fitness;         //适应度
    unsigned int parent1,parent2,cross;//双亲、交叉点
};

//新生代种群、父代种群
struct population oldpop[popsize],newpop[popsize];

//背包问题中物体重量、收益、背包容量
int weight[lchrom],profit[lchrom],contain;

//种群的总适应度、最小、最大、平均适应度
double sumfitness,minfitness,maxfitness,avgfitness;

double alpha;//计算适应度时使用的惩罚函数系数

int minpop,maxpop;//一个种群中最大和最小适应度的个数


//计算个体重量
double cal_weight(unsigned int *chr)
{
    double pop_weight=0;

    for(int i=0;i<lchrom;i++)
    {
        pop_weight=pop_weight + (*chr)*weight[i];
        chr++;
    }
    return pop_weight;
}

//种群中个体适应度计算
double cal_fit(unsigned int *chr)
{
    double pop_profit=0;
    for(int i=0;i<lchrom;i++)
    {
        pop_profit=pop_profit + (*chr)*profit[i];
        chr++;
    }
    return pop_profit;
}


void initpop()
{

    bool ispop=false;
    double tmpWeight;

    for(int i=0;i<popsize;i++)
    {
        while(!ispop)
        {
            for(int j=0;j<lchrom;j++)
            {
                oldpop[i].chrom[j]=rand()%2;
                tmpWeight=cal_weight(oldpop[i].chrom);

                if(tmpWeight<=contain)
                {
                    oldpop[i].fitness=cal_fit(oldpop[i].chrom);
                    oldpop[i].weight=tmpWeight;
                    oldpop[i].parent1=0;
                    oldpop[i].parent2=0;
                    oldpop[i].cross=0;
                    ispop=true;
                }
                else
                    ispop=false;
            }
        }

    }
}


void statistics(struct population *pop)
{
    double tmp_fit;
    sumfitness=pop[0].fitness;
    minfitness=pop[0].fitness;
    maxfitness=pop[0].fitness;
    maxpop=0;
    minpop=0;

    for(int i=1;i<popsize;i++)
    {
        sumfitness=sumfitness+pop[i].fitness;
        tmp_fit=pop[i].fitness;
        if (tmp_fit>maxfitness)
        {
            maxfitness=pop[i].fitness;
            maxpop=i;
        }
        if (tmp_fit<minfitness)
        {
            minfitness=pop[i].fitness;
            minpop=i;
        }

        avgfitness=sumfitness/(float)popsize;
    }
}

int selection()
{
    double wheel_pos;
    double rand_Number,partsum;
    int parent;

    rand_Number=(rand()%2001)/2000.0;

    wheel_pos=rand_Number*sumfitness;
    partsum=0;
    parent=0;

    do{
        partsum=partsum+oldpop[parent].fitness;
        parent=parent+1;
    }while (partsum<wheel_pos && parent<popsize);

    return parent-1;
}

int execise(double probability)
{
    double pp=(double)(rand()%20001/20000.0);

    if(pp<probability)
        return 0;

    return 1;
}

int crossover(unsigned int *parent1,unsigned int *parent2,int i)
{
    int j,cross_pos;      //生成交叉位置
	if(execise(pc))  //0,1,...(lchrom-2)
        cross_pos=rand()%(lchrom-1);
	else
        cross_pos=lchrom-1;
    for (j=0;j<=cross_pos;j++)
    {
        newpop[i].chrom[j]=parent1[j];
    }
    for(j=cross_pos+1;j<=(lchrom-1);j++)
    {
        newpop[i].chrom[j]=parent2[j];
    }
    newpop[i].cross=cross_pos;
    return 1;
}

int mutation(unsigned int alleles)
{
   if (execise(pm))
   {
     if (alleles)
        alleles=0;
     else
        alleles=1;
   }
   return alleles;
}


void generation()
{
    unsigned int i,j,mate1,mate2;
    double tmpWeight;
    int ispop;
    i=0;
    while(i<popsize)
    {
        ispop=false;
        while (!ispop)
        {
            mate1=selection();
            mate2=selection();
            crossover(oldpop[mate1].chrom,oldpop[mate2].chrom,i);
            for (j=0;j<lchrom;j++)  //变异
                newpop[i].chrom[j] = mutation(newpop[i].chrom[j]);

            //选择重量小于背包容量的个体
            tmpWeight=cal_weight(newpop[i].chrom);
            if (tmpWeight<=contain)
            {
                newpop[i].fitness=cal_fit(newpop[i].chrom);
                newpop[i].weight=tmpWeight;
                newpop[i].parent1=mate1;
                newpop[i].parent2=mate2;
                ispop=true;   //是一个解
            }
        }
        i=i+1; //此个体可以加入到种群中
    }


}

void read_infor(){
    for(int i=0;i<lchrom;i++)
    {
        weight[i]=rand()%101;
        profit[i]=rand()%101;
    }
    contain=rand()%100001;
}


//输出种群信息:种群代数，最大适应度及个体
void report(struct population * pp,int n)
{
    printf("种群代数  :  %d\n",n);
    printf("最大适应度： %f\n",maxfitness);
    printf("个体      :\n");

    for(int i=0;i<lchrom;i++)
        printf("%d  ",pp[maxpop].chrom[i]);
    printf("\n");
}



int main()
{
    srand( (unsigned)time( NULL ) ); //置随机种子

    int gen,oldmaxpop,k;
    double oldmax;
    gen=0;
    read_infor(); //读入背包信息


    time_t start,finish;

    start = clock();

    initpop();
    memcpy(&newpop,&oldpop,popsize*sizeof(struct population));
    statistics(newpop);  //统计新生种群的信息
    report(newpop,gen); //输出种群信息:种群代数，最大适应度及个体

    while(gen<maxgen)
    {
        gen=gen+1;
        if(gen%100==0) //置随机种子
            srand( (unsigned)time( NULL ));

        oldmax=maxfitness;
        oldmaxpop=maxpop;
        generation();
        statistics(newpop);
        if (maxfitness<oldmax)
        {
            for(k=0;k<lchrom;k++) //记下当前最优解
                newpop[minpop].chrom[k]=oldpop[oldmaxpop].chrom[k];
            newpop[minpop].fitness=oldpop[oldmaxpop].fitness;
            newpop[minpop].parent1=oldpop[oldmaxpop].parent1;
            newpop[minpop].parent2=oldpop[oldmaxpop].parent2;
            newpop[minpop].cross=oldpop[oldmaxpop].cross;
            statistics(newpop);
        }
        else if (maxfitness>oldmax)
            report(newpop,gen);

        memcpy(&oldpop,&newpop,popsize*sizeof(struct population));
    }

    printf("It is over.\n");
    finish = clock();

    double duration = ((double)(finish-start))/CLOCKS_PER_SEC; // 计算时间
    printf("程序运行耗时:%lf秒.\n",duration);
    return 0;
}
