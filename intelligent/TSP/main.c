#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define T0 20000.0  // ��ʼ�¶�
#define T_end (1e-8)
#define q  0.98     // �˻�ϵ��
#define L 1000      // ÿ���¶�ʱ�ĵ�������������������ѭ����ֹ������
#define N 31        // ��������

int city_list[N]; // ���ڴ��һ����
double city_pos[N][2] = {
    {1304,2312},{3639,1315},{4177,2244},{3712,1399},{3488,1535},
    {3326,1556},{3238,1229},{4196,1004},{4312,790}, {4386,570},
    {3007,1970},{2562,1756},{2788,1491},{2381,1676},{1332,695},
    {3715,1678},{3918,2179},{4061,2370},{3780,2212},{3676,2578},
    {4029,2838},{4263,2931},{3429,1908},{3507,2367},{3394,2643},
    {3439,3201},{2935,3240},{3140,3550},{2545,2357},{2778,2826},
    {2370,2975}}; //31���������ꣻ���б�ţ�1��2��3��......31





//��������
double distance(double *,double *); // �����������о���
double path_len(int *);  // ����·������
void  init();  //��ʼ������
void create_new(); // �����½�


//���뺯��
double distance(double * city1,double * city2)
{
    double x1 = *city1;
    double y1 = *(city1+1);
    double x2 = *(city2);
    double y2 = *(city2+1);
    double dis = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return dis;
}

//����·������
double CalCulate_length(int * arr)
{
    double path = 0; // ��ʼ��·������
    int index = *arr; // ��λ����һ������(�������)
    for(int i=0;i<N-1;i++)
    {
        int index1 = *(arr+i);
        int index2 = *(arr+i+1);
        double dis = distance(city_pos[index1-1],city_pos[index2-1]);
        path += dis;
    }
    int last_index = *(arr+N-1); // ���һ���������
    int first_index = *arr; // ��һ���������

    double last_dis = distance(city_pos[last_index-1],city_pos[first_index-1]);
    path = path + last_dis;

    return path; // �����ܵ�·������
}


//��ʼ������
void init()
{
    for(int i=0;i<N;i++)
        city_list[i] = i+1;  // ��ʼ��һ����
}


//2-OPT�����������ھ�
void getNewSolution()
{
    double r1 = ((double)rand())/(RAND_MAX+1.0);
    double r2 = ((double)rand())/(RAND_MAX+1.0);
    int pos1 = (int)(N*r1); //��һ��������λ��
    int pos2 = (int)(N*r2);
    int temp = city_list[pos1];
    city_list[pos1] = city_list[pos2];
    city_list[pos2] = temp;   // ����������
}


int main(void)
{
    srand((unsigned)time(NULL)); //��ʼ�����������

    time_t start,finish;
    start = clock(); // �������п�ʼ��ʱ

    double T;

    int count = 0; // ��¼���´���
    T = T0; //��ʼ�¶�
    init(); //��ʼ��һ����
    int city_list_copy[N]; // ���ڱ���ԭʼ��
    double f1,f2,df; //f1Ϊ��ʼ��Ŀ�꺯��ֵ��f2Ϊ�½�Ŀ�꺯��ֵ��dfΪ���߲�ֵ
    double r; // 0-1֮�������������������Ƿ�����½�


    while(T > T_end) // ���¶ȵ��ڽ����¶�ʱ���˻����
    {
         for(int i=0;i<L;i++)
         {
             memcpy(city_list_copy,city_list,N*sizeof(int)); // ��������
             getNewSolution(); // �����½�


             f1 = CalCulate_length(city_list_copy);//�ɽ��·��
             f2 = CalCulate_length(city_list);     //�½��·��
             df = f2 - f1;

             // ������Metropolis׼��
             if(df >= 0)//����½�Ⱦɽ���ţ���һ�����ʽ����½�
             {
                 r = ((double)rand())/(RAND_MAX);
                 if(exp(-df/T) <= r) // ����ԭ���Ľ�
                 {
                     memcpy(city_list,city_list_copy,N*sizeof(int));
                 }
             }
         }

         T = T * q; // ����
         count++;
    }

    finish = clock(); // �˻���̽���


    double duration = ((double)(finish-start))/CLOCKS_PER_SEC; // ����ʱ��
    printf("����ģ���˻��㷨������������⣬\n��ʼ�¶�T0=%.2f, \n����ϵ��q=%.2f, \nÿ���¶ȵ���%d��,\n������%d�Σ�\n\n�õ���TSP����·��Ϊ:\n",T0,q,L,count);


    // �������·��
    for(int i=0;i<=N-1;i++)
    {
        printf("%d--->",city_list[i]);
    }
    printf("%d\n",city_list[0]);


    double len = CalCulate_length(city_list); // ����·������
    printf("����·������Ϊ:%lf\n",len);
    printf("�������к�ʱ:%lf��.\n",duration);
    return 0;
}
