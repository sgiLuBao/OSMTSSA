#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
using namespace std;
const int popsize= 100; //种群规模
const int evaluations= 1000; //最大演化代数
const int endeval=evaluations;
const double w_start=0.95;
const double w_end=0.4;
const int w_varyfor=evaluations;
double w_now;
const double inerdec=(w_start-w_end)/w_varyfor;
const double c1_start=0.9;
const double c1_end=0.45;
const int c1_varyfor=evaluations;
double c1_now;
double c2_now;
const double c1_dec=(c1_start-c1_end)/c1_varyfor;
const int MAX=1010;
const double P=0.7071;//存储sqrt(2)/2的值，便于旋转直线用
int vertice;//漏点数，
double graph[MAX][2]={0},graphw[MAX][MAX]={0}; //点坐标，点两两之间距离网络图
int min_tree[3010]={0}; //存放每一个临时生成的粒子
struct pop
{
	int edge[3010];
	double fit_value;
}pop[popsize + 1], pbest[popsize + 1], gbest, pop2[popsize + 1];
 double evalgbest[100010];
 double fave=0, ffmin=10000000, ffmax=0;
 //parameters of GA
 const double pm = 0.01;
 

