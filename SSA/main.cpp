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
#include"GetCrossover_global_bydef.cpp"
#include"Dividepop.cpp"
#include"NsIndex.cpp"
#include"updateBest.cpp"
#include"refine.cpp"
#include"adjusting.cpp"

bool se(struct record2 a, struct record2 b)
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
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
		if(eval>1)
		{
			w_now=w_now-inerdec; 
			ST_now=1-w_now;
//            c1_now=c1_now-c1_dec;
			c1_now=1;
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
			    double R=rand()/(RAND_MAX+1.0); //产生随机数
			    double CRr=rand()/(RAND_MAX+1.0); //产生随机数
			    int jrr=rand() % popsize + 1;  //生成一个1-popsize的随机数
			  //变异pop(i) 
			  if(R>=ST_now){ 
			  		if(CRr<CRR || jrr==i){
			  			GetMutation(i);
			  			GetCrossover_self(i);
			  			GetCrossover_global(i);
					  }else{
					  	GetCrossover_rand(i); //变异后的pop(i)与pbest(i)进行交叉 
					  	GetCrossover_global(i); 
					  }
			  		
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
			double CRr=rand()/(RAND_MAX+1.0); //产生随机数
			int jrr=rand() % popsize + 1;  //生成一个1-popsize的随机数
			//第一阶段 
			if(i>(popsize/2)){
				if(CRr<CRR || jrr==i){
			  		GetMutation(i);
			  		GetCrossover_self(i);
			  		GetCrossover_global(i);
				}
				else{
					InitializeTree();  
	  		        for(j=1;j<=3*(vertice-1);j++)
			       		randP.edge[j]=min_tree[j]; 	
//			       	GetMutation(i);
			  		GetCrossover_worstr_bydef(i); 
				}
			}else{
			  GetCrossover_xp(i); 
			  GetMutation_SSA(i);
			  GetCrossover_xp(i); //全局感知
			} 
		}
		//侦察者
		NsIndex();//计算侦察者下标 
		for(i=1;i<=80;i++) {
			if(NS[i].fit_value>min_fitness){
//				GetCrossover_global_bydef(i); 
				GetMutation_SSA(i);
				GetCrossover_global(i); //全局感知
			}
			else{
				double CRr=rand()/(RAND_MAX+1.0); //产生随机数
			    int jrr=rand() % popsize + 1;  //生成一个1-popsize的随机数
				if(CRr<CRR || jrr==i){
			  		GetMutation(i);
			  		GetCrossover_self(i);
			  		GetCrossover_global(i);
				}
				else{
					GetMutation_SSA(i);
				    GetCrossover_self(i);
//				    GetCrossover_global(i);	
				}
			}
		}
		//更新个体最优pbest ,全局最优值min_fitness，gbest 
		updateBest();
		eval++;
	}
	printf("\n最优粒子的总线长为：%lf\n",gbest.fit_value);
	bfgbestF = gbest.fit_value;
	clock_t finish2=clock();
	printf("flying time:%lf\n",(double)(finish2-start2)/CLOCKS_PER_SEC);
	
	for(i=1;i<=(vertice-1);i++)
   {
	   min_tree[i*3-2]=gbest.edge[i*3-2];
	   min_tree[i*3-1]=gbest.edge[i*3-1];
	   min_tree[i*3]=gbest.edge[i*3];
   }
   sign=0; 
   Getfitness();

   if(sign)  
   {
//	   printf("fail! Select extra point!\n");
	   clock_t start3=clock();
	   while(1)
	   {
		  adjusting(); 
		  FILE *fin;
	      fin=fopen("steiner.txt","r");
	      fscanf(fin,"%d",&extra_num);
		  
//		  printf("extra_num:%d\n",extra_num);
   
	      for(i=1;i<=extra_num;i++) 
		   fscanf(fin,"%lf%lf",&graph[vertice+i][0],&graph[vertice+i][1]);
          fclose(fin);

		  for(i=1;i<=(vertice-1);i++)
		  {
			  mres[i].s=min_tree[i*3-2];
			  mres[i].e=min_tree[i*3-1];
			  mres[i].c=min_tree[i*3];
		  }
		 
	      fin=fopen("delete.txt","r");
	      fscanf(fin,"%d",&del_num);	
//		  printf("del_num:%d\n",del_num);
	      for(i=1;i<=del_num;i++)
            fscanf(fin,"%d %d %d",&del[i].s,&del[i].e,&del[i].c);
		  fclose(fin);
		  
		  sort(mres+1,mres+vertice,se);
		  sort(del+1,del+del_num+1,se);
//		  for(i=1;i<=del_num;i++)
//		    printf("%d %d %d\n",del[i].s,del[i].e,del[i].c);
//		  for(i=1;i<=vertice-1;i++)
//			  printf("%d:%d %d %d\n",i,mres[i].s,mres[i].e,mres[i].c);
		 
		  i=1;j=1;pp=1;
		  while(i<=vertice-1) 
		  {
			  if(j<=del_num&&mres[i].s==del[j].s&&mres[i].e==del[j].e&&mres[i].c==del[j].c)
			  {
                i++;
				j++;
			  }
			  else
			  {
                 res[pp].s=mres[i].s;
				 res[pp].e=mres[i].e;
				 res[pp++].c=mres[i++].c;
			  }
		  }
		  vertice+=extra_num;

//		  printf("vertice:%d\n",vertice);

		  FLAG=0;
		  fin=fopen("add.txt","r");
		  fscanf(fin,"%d",&add_num);

//		  printf("add_num:%d\n",add_num);
//		  printf("pp:%d\n",pp);
		  for(i=pp;i<pp+add_num;i++)
		  {
             fscanf(fin,"%d %d %d",&res[i].s,&res[i].e,&res[i].c);
			 CH=-1;
			 pre(res[i].s,res[i].e); 
			 if(CH!=-1) res[i].c=CH;
			 else FLAG=1;
		  }

		  fclose(fin);
		 
//		  for(i=1;i<pp+add_num;i++)
//			  printf("%d: %d %d %d\n",i,res[i].s,res[i].e,res[i].c);
//		  printf("FLAG:%d\n",FLAG);

		  if(!FLAG) 
		  {
             for(i=1;i<=(vertice-1);i++)
			  {
	              gbest.edge[i*3-2]=res[i].s;				 
	              gbest.edge[i*3-1]=res[i].e;				  
	              gbest.edge[i*3]=res[i].c;
			  }
			  break;
		  }
		  else 
		  {
              for(i=1;i<=(vertice-1);i++)
			  {
	              min_tree[i*3-2]=res[i].s;				 
	              min_tree[i*3-1]=res[i].e;				  
	              min_tree[i*3]=res[i].c;
			  }
		  }
	   }
	   clock_t finish3=clock();
	   printf("adjusting time:%lf\n",(double)(finish3-start3)/CLOCKS_PER_SEC);
       FILE *fout;
       fout=fopen("point.txt","w"); 
       	fprintf(fout,"%d\n",vertice);
	   for(i=1;i<=vertice;i++)
		fprintf(fout,"%.0lf %.0lf\n",graph[i][0],graph[i][1]);  
	   fclose(fout);
	   printf("after adjusting success!\n");
   }
   else
	   printf("directly success!\n");
    for(i=1;i<=(vertice-1);i++)
	   {
	     min_tree[i*3-2]=gbest.edge[i*3-2];
	     min_tree[i*3-1]=gbest.edge[i*3-1];
	     min_tree[i*3]=gbest.edge[i*3];
	   }
	gbest.fit_value=Getfitness();
	printf("before refine:%lf\n",gbest.fit_value);
	FILE *fout;
	fout=fopen("rrr.txt","w");
	for(j=1;j<=3*(vertice-1);j++)
		fprintf(fout,"%d ",gbest.edge[j]);
	fprintf(fout,"\n%lf",gbest.fit_value);
	fclose(fout);
	clock_t start4=clock();
    refine();
	clock_t finish4=clock();
	   printf("refine time:%lf\n",(double)(finish4-start4)/CLOCKS_PER_SEC);
    printf("result：%lf\n",gbest.fit_value);

	fout=fopen("result.txt","w");
	for(j=1;j<=3*(vertice-1);j++)
		fprintf(fout,"%d ",gbest.edge[j]);
	fprintf(fout,"\n%lf",gbest.fit_value);
	fclose(fout);
	FILE *fp;
	fp = fopen("C:\\Users\\zly\\Desktop\\SSA.xlsx","a") ;//不想覆盖就用a 
	fprintf(fp,"%lf\t%lf\n",bfgbestF,gbest.fit_value) ;
	fclose(fp);
	return 0;
}

