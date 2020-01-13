#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define popsize 200   //��Ⱥ�Ĺ�ģ
#define pc      0.618 //�������
#define pm      0.03  //�������
#define lchrom  90    //Ⱦɫ�峤��
#define maxgen  1000  //����������
typedef enum __bool { false = 0, true = 1, } bool;

struct population{
    unsigned int chrom[lchrom];//Ⱦɫ��
    double weight;          //��������
    double fitness;         //��Ӧ��
    unsigned int parent1,parent2,cross;//˫�ס������
};

//��������Ⱥ��������Ⱥ
struct population oldpop[popsize],newpop[popsize];

//�����������������������桢��������
int weight[lchrom],profit[lchrom],contain;

//��Ⱥ������Ӧ�ȡ���С�����ƽ����Ӧ��
double sumfitness,minfitness,maxfitness,avgfitness;

double alpha;//������Ӧ��ʱʹ�õĳͷ�����ϵ��

int minpop,maxpop;//һ����Ⱥ��������С��Ӧ�ȵĸ���


//�����������
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

//��Ⱥ�и�����Ӧ�ȼ���
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
    int j,cross_pos;      //���ɽ���λ��
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
            for (j=0;j<lchrom;j++)  //����
                newpop[i].chrom[j] = mutation(newpop[i].chrom[j]);

            //ѡ������С�ڱ��������ĸ���
            tmpWeight=cal_weight(newpop[i].chrom);
            if (tmpWeight<=contain)
            {
                newpop[i].fitness=cal_fit(newpop[i].chrom);
                newpop[i].weight=tmpWeight;
                newpop[i].parent1=mate1;
                newpop[i].parent2=mate2;
                ispop=true;   //��һ����
            }
        }
        i=i+1; //�˸�����Լ��뵽��Ⱥ��
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


//�����Ⱥ��Ϣ:��Ⱥ�����������Ӧ�ȼ�����
void report(struct population * pp,int n)
{
    printf("��Ⱥ����  :  %d\n",n);
    printf("�����Ӧ�ȣ� %f\n",maxfitness);
    printf("����      :\n");

    for(int i=0;i<lchrom;i++)
        printf("%d  ",pp[maxpop].chrom[i]);
    printf("\n");
}



int main()
{
    srand( (unsigned)time( NULL ) ); //���������

    int gen,oldmaxpop,k;
    double oldmax;
    gen=0;
    read_infor(); //���뱳����Ϣ


    time_t start,finish;

    start = clock();

    initpop();
    memcpy(&newpop,&oldpop,popsize*sizeof(struct population));
    statistics(newpop);  //ͳ��������Ⱥ����Ϣ
    report(newpop,gen); //�����Ⱥ��Ϣ:��Ⱥ�����������Ӧ�ȼ�����

    while(gen<maxgen)
    {
        gen=gen+1;
        if(gen%100==0) //���������
            srand( (unsigned)time( NULL ));

        oldmax=maxfitness;
        oldmaxpop=maxpop;
        generation();
        statistics(newpop);
        if (maxfitness<oldmax)
        {
            for(k=0;k<lchrom;k++) //���µ�ǰ���Ž�
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

    double duration = ((double)(finish-start))/CLOCKS_PER_SEC; // ����ʱ��
    printf("�������к�ʱ:%lf��.\n",duration);
    return 0;
}
