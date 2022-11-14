int parent1[MAX];
void initial1(int n) 
{
	int i;
	for(i=1;i<=n;i++)
	   parent1[i]=i;
}
int find_set1(int x) 
{
 int temp;
 if(parent1[x]==x) return x;
 else
 {
  temp=parent1[x];
  parent1[x]=find_set1(temp); 
  return parent1[x];
 }
}
void union_set1(int a,int b)
{
  int pa,pb;
  pa=find_set1(a);
  pb=find_set1(b);
  if(pa!=pb) 
  parent1[pb]=pa;
}
struct tree 
{
	int s,e;
	int line_style;
}par[1010],par_best[1010],sur[2020],new_res[1010];
bool cmpp(struct tree a,struct tree b)
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_global(int cur)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
	
//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//	printf("当前粒子的适应度：%lf\n\n",pop[cur].fit_value);
//	printf("全局历史最优粒子的适应度：%lf\n\n",gbest.fit_value);

    if(c<c2_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par[i].s=pop[cur].edge[i*3-2]; 
		 par[i].e=pop[cur].edge[i*3-1];
		 par[i].line_style=pop[cur].edge[i*3];
		 if(par[i].s>par[i].e) 
		 {
			 mid=par[i].s;
			 par[i].s=par[i].e;
			 par[i].e=mid;
			 if(par[i].line_style==0||par[i].line_style==1)
                 par[i].line_style=!par[i].line_style;
			 else if(par[i].line_style==2)
			     par[i].line_style=3;
			 else if(par[i].line_style==3)
				 par[i].line_style=2;
		 }
	  }

	  
 //   printf("par粒子：\n");
 //   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par[i].s,par[i].e,par[i].line_style);
//	  printf("\n");

	  for(i=1;i<=(vertice-1);i++)
	  {
         par_best[i].s=gbest.edge[i*3-2];
		 par_best[i].e=gbest.edge[i*3-1];
		 par_best[i].line_style=gbest.edge[i*3];
		 if(par_best[i].s>par_best[i].e)
		 {
			 mid=par_best[i].s;
			 par_best[i].s=par_best[i].e;
			 par_best[i].e=mid;
			 if(par_best[i].line_style==0||par_best[i].line_style==1)
                 par_best[i].line_style=!par_best[i].line_style;
			 else if(par_best[i].line_style==2)
			     par_best[i].line_style=3;
			 else if(par_best[i].line_style==3)
				 par_best[i].line_style=2;
		 }
	  }
//	  printf("par_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par_best[i].s,par_best[i].e,par_best[i].line_style);
//	  printf("\n");



	  sort(par+1,par+vertice,cmpp); 
      sort(par_best+1,par_best+vertice,cmpp);

//	     printf("排序后par粒子：\n");
 //     for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par[i].s,par[i].e,par[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par_best粒子：\n");
// for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par_best[i].s,par_best[i].e,par_best[i].line_style);
//	  printf("\n");

	  initial1(vertice);
	  for(i=1;i<=(vertice-1);i++)
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; 
      for(i=1;i<=(vertice-1);i++)
	  {
         for(j=1;j<=(vertice-1);j++)  
		 {
            if(par_best[j].s==par[i].s) 
				break;
		 }
		 for(;j<=(vertice-1);j++) 
		 {
			 if(par_best[j].s!=par[i].s)  
				 break;
			 if(par_best[j].e==par[i].e) 
			 {
                sign1[i]=1; 
				sign2[j]=1; 
				union_set1(par[i].s,par[i].e); 
                new_res[count_new].s=par_best[j].s; 
				new_res[count_new].e=par_best[j].e;
				new_res[count_new++].line_style=par_best[j].line_style;
				break;
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res[i].s,new_res[i].e,new_res[i].line_style);
//	  printf("\nsign1:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

	  count_sur=1; 
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur[count_sur].s=par[i].s;
			  sur[count_sur].e=par[i].e;
			  sur[count_sur++].line_style=par[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur[count_sur].s=par_best[i].s;
			  sur[count_sur].e=par_best[i].e;
			  sur[count_sur++].line_style=par_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur:%d\n",count_sur);
//	  for(i=1;i<count_sur;i++)
//	    printf("%d %d %d\n",sur[i].s,sur[i].e,sur[i].line_style);
//	  printf("\n");


	  while(1)
	  {
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur-1))+1;
          if(find_set1(sur[i].s)!=find_set1(sur[i].e))
		  {
             new_res[count_new].s=sur[i].s; 
			 new_res[count_new].e=sur[i].e;
			 new_res[count_new++].line_style=sur[i].line_style;
			 union_set1(sur[i].s,sur[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop[cur].edge[i*3-2]=new_res[i].s;
          pop[cur].edge[i*3-1]=new_res[i].e;
          pop[cur].edge[i*3]=new_res[i].line_style;
	  }

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 
	}
}