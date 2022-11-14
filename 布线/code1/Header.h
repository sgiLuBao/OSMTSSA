#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<vector>

#include <set>
#include<map>
#include<queue>
using namespace std;
#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b

using namespace std;
const int popsize=100; 
const int evaluations=100; 
const int endeval=evaluations;
const double w_start=0.95;
const double w_end=0.4;
const int w_varyfor=evaluations;
double w_now;
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
bool cor_sign[10010][4]={false};
struct pop
{
	int edge[3*MAX+10];
	double fit_value;
	int source;
	double maxPL;
}pop[popsize+1],pbest[popsize+1],gbest; 
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

double R_source = 180.0; //源点电阻
double C_sink = 23.40; //汇点电容
double r_0 = 0.0075; //单位长度导线电阻
double c_0 = 0.118;  //单位长度导线电容
struct pinslack 
{
	double delay;
	double AAT;
	double RAT;
	double slack;
	int bj;
}pinslack[MAX];
map<int, int> leaves; //<sink,pos>
map<int,int> pin2edge;
 //存储下游电容
map<int, double> DownCaps; //<point,downstreamCap>
map<int,vector<int> > mtree;
map<int ,int> father; // i with its father
map<int,double> ratvalue; 
