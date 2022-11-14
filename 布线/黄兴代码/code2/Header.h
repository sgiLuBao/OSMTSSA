#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
using namespace std;
const int MAX=2000;
int sign,FLAG; 
const double P=0.7071;
int ini_v_num;
int vertice,barr_num,tri_num,edge_num;
int extra_num,del_num,add_num;
double graph[MAX][3],barr[10010][4];
bool s[MAX][MAX]={false};
bool cor_sign[10010][4]={false};
bool edge_sign[MAX]={false};
int refine_sum,times;
double final_len;
int del_index[1000][1000],dc;
//struct par
//{
//	int sum;
//	int code_pos[5];
//}pin[MAX];
struct record1 
{
	int c[4]; 
	int serial_num[4][1000]; 
    double semiperimeter[4]; 
}records1[MAX*3];
struct record
{  
  double posh,sh,eh; 
  double posv,sv,ev;
  double pos45,s45,e45;
  double pos135,s135,e135;
  bool mark[4]; 
}records2[MAX*3][4];
struct record2
{
	int s,e,c,index;
    bool mark;
}edge[MAX],mres[MAX],del[MAX];
struct record3
{
	int a,b,c;
}triangle[MAX*4];
struct term
{
	int degree; 
	int edge_pos[10];
}terminal[MAX*2];
struct str
{
   int num;
   int choice[4];
   double ll;
   double shared_value;
}opt_str[MAX*2];


