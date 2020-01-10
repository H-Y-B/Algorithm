#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define T0 20000.0  // 初始温度
#define T_end (1e-8)
#define q  0.98     // 退火系数
#define L 1000      // 每个温度时的迭代次数，即链长（内循环终止条件）
#define N 31        // 城市数量

int city_list[N]; // 用于存放一个解
double city_pos[N][2] = {
    {1304,2312},{3639,1315},{4177,2244},{3712,1399},{3488,1535},
    {3326,1556},{3238,1229},{4196,1004},{4312,790}, {4386,570},
    {3007,1970},{2562,1756},{2788,1491},{2381,1676},{1332,695},
    {3715,1678},{3918,2179},{4061,2370},{3780,2212},{3676,2578},
    {4029,2838},{4263,2931},{3429,1908},{3507,2367},{3394,2643},
    {3439,3201},{2935,3240},{3140,3550},{2545,2357},{2778,2826},
    {2370,2975}}; //31个城市坐标；城市编号：1、2、3、......31





//函数声明
double distance(double *,double *); // 计算两个城市距离
double path_len(int *);  // 计算路径长度
void  init();  //初始化函数
void create_new(); // 产生新解


//距离函数
double distance(double * city1,double * city2)
{
    double x1 = *city1;
    double y1 = *(city1+1);
    double x2 = *(city2);
    double y2 = *(city2+1);
    double dis = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return dis;
}

//计算路径长度
double CalCulate_length(int * arr)
{
    double path = 0; // 初始化路径长度
    int index = *arr; // 定位到第一个数字(城市序号)
    for(int i=0;i<N-1;i++)
    {
        int index1 = *(arr+i);
        int index2 = *(arr+i+1);
        double dis = distance(city_pos[index1-1],city_pos[index2-1]);
        path += dis;
    }
    int last_index = *(arr+N-1); // 最后一个城市序号
    int first_index = *arr; // 第一个城市序号

    double last_dis = distance(city_pos[last_index-1],city_pos[first_index-1]);
    path = path + last_dis;

    return path; // 返回总的路径长度
}


//初始化函数
void init()
{
    for(int i=0;i<N;i++)
        city_list[i] = i+1;  // 初始化一个解
}


//2-OPT交换法生成邻居
void getNewSolution()
{
    double r1 = ((double)rand())/(RAND_MAX+1.0);
    double r2 = ((double)rand())/(RAND_MAX+1.0);
    int pos1 = (int)(N*r1); //第一个交叉点的位置
    int pos2 = (int)(N*r2);
    int temp = city_list[pos1];
    city_list[pos1] = city_list[pos2];
    city_list[pos2] = temp;   // 交换两个点
}


int main(void)
{
    srand((unsigned)time(NULL)); //初始化随机数种子

    time_t start,finish;
    start = clock(); // 程序运行开始计时

    double T;

    int count = 0; // 记录降温次数
    T = T0; //初始温度
    init(); //初始化一个解
    int city_list_copy[N]; // 用于保存原始解
    double f1,f2,df; //f1为初始解目标函数值，f2为新解目标函数值，df为二者差值
    double r; // 0-1之间的随机数，用来决定是否接受新解


    while(T > T_end) // 当温度低于结束温度时，退火结束
    {
         for(int i=0;i<L;i++)
         {
             memcpy(city_list_copy,city_list,N*sizeof(int)); // 复制数组
             getNewSolution(); // 产生新解


             f1 = CalCulate_length(city_list_copy);//旧解的路径
             f2 = CalCulate_length(city_list);     //新解的路径
             df = f2 - f1;

             // 以下是Metropolis准则
             if(df >= 0)//如果新解比旧解更优，以一定概率接受新解
             {
                 r = ((double)rand())/(RAND_MAX);
                 if(exp(-df/T) <= r) // 保留原来的解
                 {
                     memcpy(city_list,city_list_copy,N*sizeof(int));
                 }
             }
         }

         T = T * q; // 降温
         count++;
    }

    finish = clock(); // 退火过程结束


    double duration = ((double)(finish-start))/CLOCKS_PER_SEC; // 计算时间
    printf("采用模拟退火算法解决旅行商问题，\n初始温度T0=%.2f, \n降温系数q=%.2f, \n每个温度迭代%d次,\n共降温%d次，\n\n得到的TSP最优路径为:\n",T0,q,L,count);


    // 输出最优路径
    for(int i=0;i<=N-1;i++)
    {
        printf("%d--->",city_list[i]);
    }
    printf("%d\n",city_list[0]);


    double len = CalCulate_length(city_list); // 最优路径长度
    printf("最优路径长度为:%lf\n",len);
    printf("程序运行耗时:%lf秒.\n",duration);
    return 0;
}
