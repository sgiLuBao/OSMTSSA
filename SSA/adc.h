#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<vector >
using namespace std;
const int popsize=100; 
const int Np = 10;//发现者比例 
const int Nj = 90;//参与者比例 
const int Ns = 80;//侦察者比例 
const int evaluations=300; 
const int endeval=evaluations;
const double w_start=0.95;
const double w_end=0.4;
const int w_varyfor=evaluations;
double w_now;
double ST_now;
double CRR=0.3;
double FlyingTime;
double PretreatmentTime;
double AdjustingTime;
double afAgbestF;
double RefineTime;
const double inerdec=(w_start-w_end)/w_varyfor;
const double c1_start=0.9;
const double c1_end=0.15;
const int c1_varyfor=evaluations;
double c1_now;
double c2_now;
const double c1_dec=(c1_start-c1_end)/c1_varyfor;
const int MAX=1100;
int sign=0,FLAG,CH;
const double P=0.7071;
int vertice,barr_num,extra_num,del_num,add_num;
double graph[MAX][2]={0},graphw[MAX][MAX]={0},barr[10010][4];
int min_tree[3*MAX+10]={0}; 
int NsIdx[20]={0};
bool cor_sign[10010][4]={false};
double min_fitness;
double worst_fitness;
double bfgbestF;
struct pop
{
	int edge[3*MAX+10];
	double fit_value;
}pop[popsize+1],pbest[popsize+1],gbest,NPbest,gWorst,NP[Np+1],NJ[Nj+1],NS[Ns+1],prepop[popsize+1],randP; 
//struct record  
//{
//	int num[4];  
//}records[MAX][MAX];
struct par
{
	int sum;
	int code_pos[5];
	int p_pos[5];
}pin[MAX];
//struct record1 
//{
//	int c[4]
//	int serial_num[4][60]
//}records1[MAX][MAX];
struct record1 
{
	int c[4]; 
	int serial_num[4][50]; 
}records1[MAX][MAX];
struct record2
{
	int s,e,c;
}mres[MAX],del[MAX],res[MAX];


