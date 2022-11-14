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
		��������ģ�ͽ׶Ρ�Ԥ����׶Ρ���ʼ���������׶��뻮����Ⱥ 
	*/
	GenerateGraph();
	clock_t start1=clock();
	pre_treatment();
    clock_t finish1=clock();
	printf("pretreatment time:%lf",(double)(finish1-start1)/CLOCKS_PER_SEC);//Ԥ����ʱ��
	InitializePop();//����pop[1] - pop[popsize]
	min_fitness=pop[1].fit_value;
	worst_fitness = pop[popsize].fit_value;
	 
	/*
		���½׶� 
	*/ 
	clock_t start2=clock();
	while(eval<=evaluations)
	{
		sort(pop+1,pop+popsize+1,cmp);
		Dividepop(); //������Ⱥ�׶�:Np�������ߣ�NJ:������ 
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
        //������ 
		for(i=1;i<=Np;i++) 
		{	
			  //����pop(i) 
			  if(GetMutation_SSA(i)){
			  		GetCrossover_self(i); //������pop(i)��pbest(i)���н��� 
			  }
			  else{
			  	GetCrossover_global(i); //δ�����pop(i)�� pbest���н��� 
			  } 
		}
		sort(pop+1,pop+popsize+1,cmp);
		Dividepop();
		//������ 
		for(i=Np+1;i<=popsize;i++) 
		{
			//��һ�׶� 
			if(i>(popsize/2)){
			  GetMutation_SSA(i); //����
			  GetCrossover_self(i); 
			  GetCrossover_global(i); //ȫ�ָ�֪
			}else{
			  GetCrossover_xp(i); 
			  GetCrossover_global(i); //ȫ�ָ�֪
			} 
		}
		//�����
		NsIndex();//����������±� 
		for(i=1;i<=Ns;i++) {
			if(NS.fit_value>min_fitness){
				GetCrossover_self(i); 
				GetCrossover_global(i); //ȫ�ָ�֪
			}
			else{
				GetMutation_SSA(i); //����
				GetCrossover_self(i);
			}
		}
		//���¸�������pbest ,ȫ������ֵmin_fitness��gbest 
		updateBest();
		eval++;
	}
	printf("\n�������ӵ����߳�Ϊ��%lf\n",gbest.fit_value);
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
