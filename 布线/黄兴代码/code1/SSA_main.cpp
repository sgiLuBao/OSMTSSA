#include"adc.h"
#include"strictbarr.cpp" 
#include"GenerateGraph.cpp"
#include"pre.cpp"
#include"pre_treatment.cpp"
#include"InitializeTree.cpp"
#include"Getfitness.cpp"
#include"InitializePop.cpp"
#include"GetMutation.cpp"
#include"GetCrossover_self.cpp"
#include"GetCrossover_global.cpp"
#include"Dividepop.cpp"
#include"NsIndex.cpp"
#include"updateBest.cpp"
//#include"adjusting.cpp"
//#include"refine.cpp"


int main(){
	int eval,i,j,index,flag,pp;
	eval=1;
    index=1;
	w_now=w_start;
	c1_now=c1_start;
	srand(time(NULL));
	
	/*
		生成问题模型阶段、预处理阶段、初始化生成树阶段与划分种群 
	*/
	GenerateGraph();
	clock_t start1=clock();
	pre_treatment();
    clock_t finish1=clock();
	printf("pretreatment time:%lf",(double)(finish1-start1)/CLOCKS_PER_SEC);//预处理时间
	InitializePop();//生成pop[1] - pop[popsize]
	min_fitness=pop[1].fit_value;
	worst_fitness = pop[popsize].fit_value;
	 
	/*
		更新阶段 
	*/ 
	clock_t start2=clock();
	while(eval<=evaluations)
	{
		sort(pop+1,pop+popsize+1,cmp);
		Dividepop(); //划分种群阶段:Np：发现者；NJ:参与者 
        flag=0;
		if(eval>1)
		{
			w_now=w_now-inerdec; 
			ST_now=1-w_now;
            c1_now=c1_now-c1_dec;
		}
		c2_now=c1_now;
		if(eval==evaluations)
		{
			 w_now=0.7;
			 ST_now=1-w_now;
			 c1_now=0.6;
		     c2_now=0.5;
		 }
        //发现者 
		for(i=1;i<=Np;i++) 
		{	
			  //变异pop(i) 
			  if(GetMutation_SSA(i)){
			  		GetCrossover_self(i); //变异后的pop(i)与pbest(i)进行交叉 
			  }
			  else{
			  	GetCrossover_global(i); //未变异的pop(i)与 pbest进行交叉 
			  } 
		}
		sort(pop+1,pop+popsize+1,cmp);
		Dividepop();
		//跟随者 
		for(i=Np+1;i<=popsize;i++) 
		{
			//第一阶段 
			if(i>(popsize/2)){
			  GetMutation_SSA(i); //变异
			  GetCrossover_self(i); 
			  GetCrossover_global(i); //全局感知
			}else{
			  GetCrossover_xp(i); 
			  GetCrossover_global(i); //全局感知
			} 
		}
		//侦察者
		NsIndex();//计算侦察者下标 
		for(i=1;i<=Ns;i++) {
			if(NS.fit_value>min_fitness){
				GetCrossover_self(i); 
				GetCrossover_global(i); //全局感知
			}
			else{
				GetMutation_SSA(i); //变异
				GetCrossover_self(i);
			}
		}
		//更新个体最优pbest ,全局最优值min_fitness，gbest 
		updateBest();
		eval++;
	}
	printf("\n最优粒子的总线长为：%lf\n",gbest.fit_value);
	clock_t finish2=clock();
	printf("flying time:%lf\n",(double)(finish2-start2)/CLOCKS_PER_SEC);
}
bool se(struct record2 a, struct record2 b)
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
bool cmp(struct pop a,struct pop b)
{
	if(a.fit_value<b.fit_value)
	  return true;
	else 
	  return false ;
}
