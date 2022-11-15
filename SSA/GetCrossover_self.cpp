int parent2[MAX];
void initial2(int n) 
{
	int i;
	for(i=1;i<=n;i++)
	   parent2[i]=i;
}
int find_set2(int x) 
{
 int temp;
 if(parent2[x]==x) return x;
 else
 {
  temp=parent2[x];
  parent2[x]=find_set2(temp); 
  return parent2[x];
 }
}
void union_set2(int a,int b)
{
  int pa,pb;
  pa=find_set2(a);
  pb=find_set2(b);
  if(pa!=pb) 
  parent2[pb]=pa;
}
struct tree1 
{
	int s,e;
	int line_style;
}par1[1010],par1_best[1010],sur1[2020],new_res1[1010];
bool cmpp1(struct tree1 a,struct tree1 b) 
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_self(int cur)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur1;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
	
//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

    if(c<c1_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1[i].s=pop[cur].edge[i*3-2]; 
		 par1[i].e=pop[cur].edge[i*3-1];
		 par1[i].line_style=pop[cur].edge[i*3];
		 if(par1[i].s>par1[i].e) 
		 {
			 mid=par1[i].s;
			 par1[i].s=par1[i].e;
			 par1[i].e=mid;
			 if(par1[i].line_style==0||par1[i].line_style==1) 
                 par1[i].line_style=!par1[i].line_style;
			 else if(par1[i].line_style==2)
			     par1[i].line_style=3;
			 else if(par1[i].line_style==3)
				 par1[i].line_style=2;
		 }
	  }

	  
  //    printf("par1粒子：\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");

	  for(i=1;i<=(vertice-1);i++)//将当前粒子的历史最优解存入结构体中
	  {
         par1_best[i].s=pbest[cur].edge[i*3-2];
		 par1_best[i].e=pbest[cur].edge[i*3-1];
		 par1_best[i].line_style=pbest[cur].edge[i*3];
		 if(par1_best[i].s>par1_best[i].e)//如果起点编号大于终点编号，则交换位置
		 {
			 mid=par1_best[i].s;
			 par1_best[i].s=par1_best[i].e;
			 par1_best[i].e=mid;
			 if(par1_best[i].line_style==0||par1_best[i].line_style==1)//连接方式互换
                 par1_best[i].line_style=!par1_best[i].line_style;
			 else if(par1_best[i].line_style==2)
			     par1_best[i].line_style=3;
			 else if(par1_best[i].line_style==3)
				 par1_best[i].line_style=2;
		 }
	  }
//	  printf("par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");



	  sort(par1+1,par1+vertice,cmpp1); //对粒子的边按照起点由小到大，终点由小到大的顺序排列
      sort(par1_best+1,par1_best+vertice,cmpp1);

	//     printf("排序后par1粒子：\n");
   //   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");

	  initial2(vertice);
	  for(i=1;i<=(vertice-1);i++)//初始化标记数组，标记哪条边是共同边
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; //记录新粒子中当前的边数
      for(i=1;i<=(vertice-1);i++)//寻找两个粒子中相同的边
	  {
         for(j=1;j<=(vertice-1);j++)  //找到个体历史最优粒子中与当前粒子第i条边起点相同的位置
		 {
            if(par1_best[j].s==par1[i].s) //找到跳出
				break;
		 }
		 for(;j<=(vertice-1);j++) //个体历史最优粒子中寻找与当前粒子第i条边终点相同的边
		 {
			 if(par1_best[j].s!=par1[i].s)  //起点不同，则不存在相同的边，跳出；
				 break;
			 if(par1_best[j].e==par1[i].e) //找到相同的边
			 {
                sign1[i]=1; //当前粒子中该边标记为1
				sign2[j]=1; //个体历史最优粒子中该边标记位1
				union_set2(par1[i].s,par1[i].e); //合并该边的两个端点为同一组
                new_res1[count_new].s=par1_best[j].s; //将共同边存入new_res1中
				new_res1[count_new].e=par1_best[j].e;
				new_res1[count_new++].line_style=par1_best[j].line_style;
				break;//跳出
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res1[i].s,new_res1[i].e,new_res1[i].line_style);
//	  printf("\nsign1:\n");
 //     for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

	  count_sur1=1; //记录挑完共同边后剩余的边数
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur1[count_sur1].s=par1[i].s;
			  sur1[count_sur1].e=par1[i].e;
			  sur1[count_sur1++].line_style=par1[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur1[count_sur1].s=par1_best[i].s;
			  sur1[count_sur1].e=par1_best[i].e;
			  sur1[count_sur1++].line_style=par1_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur1:%d\n",count_sur1);
//	  for(i=1;i<count_sur1;i++)
//	    printf("%d %d %d\n",sur1[i].s,sur1[i].e,sur1[i].line_style);
//	  printf("\n");

	  while(1)
	  {
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur1-1))+1;
          if(find_set2(sur1[i].s)!=find_set2(sur1[i].e))
		  {
             new_res1[count_new].s=sur1[i].s; 
			 new_res1[count_new].e=sur1[i].e;
			 new_res1[count_new++].line_style=sur1[i].line_style;
			 union_set2(sur1[i].s,sur1[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop[cur].edge[i*3-2]=new_res1[i].s;
          pop[cur].edge[i*3-1]=new_res1[i].e;
          pop[cur].edge[i*3]=new_res1[i].line_style;
	  }

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 

//	  printf("适应度：%lf\n",pop[cur].fit_value);
	}
}

void GetCrossover_self_SSA(int cur,int CrRate)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur1;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
	
//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

    if(c<CrRate)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1[i].s=pop[cur].edge[i*3-2]; 
		 par1[i].e=pop[cur].edge[i*3-1];
		 par1[i].line_style=pop[cur].edge[i*3];
		 if(par1[i].s>par1[i].e) 
		 {
			 mid=par1[i].s;
			 par1[i].s=par1[i].e;
			 par1[i].e=mid;
			 if(par1[i].line_style==0||par1[i].line_style==1) 
                 par1[i].line_style=!par1[i].line_style;
			 else if(par1[i].line_style==2)
			     par1[i].line_style=3;
			 else if(par1[i].line_style==3)
				 par1[i].line_style=2;
		 }
	  }

	  
  //    printf("par1粒子：\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");

	  for(i=1;i<=(vertice-1);i++)//将当前粒子的历史最优解存入结构体中
	  {
         par1_best[i].s=pbest[cur].edge[i*3-2];
		 par1_best[i].e=pbest[cur].edge[i*3-1];
		 par1_best[i].line_style=pbest[cur].edge[i*3];
		 if(par1_best[i].s>par1_best[i].e)//如果起点编号大于终点编号，则交换位置
		 {
			 mid=par1_best[i].s;
			 par1_best[i].s=par1_best[i].e;
			 par1_best[i].e=mid;
			 if(par1_best[i].line_style==0||par1_best[i].line_style==1)//连接方式互换
                 par1_best[i].line_style=!par1_best[i].line_style;
			 else if(par1_best[i].line_style==2)
			     par1_best[i].line_style=3;
			 else if(par1_best[i].line_style==3)
				 par1_best[i].line_style=2;
		 }
	  }
//	  printf("par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");



	  sort(par1+1,par1+vertice,cmpp1); //对粒子的边按照起点由小到大，终点由小到大的顺序排列
      sort(par1_best+1,par1_best+vertice,cmpp1);

	//     printf("排序后par1粒子：\n");
   //   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");

	  initial2(vertice);
	  for(i=1;i<=(vertice-1);i++)//初始化标记数组，标记哪条边是共同边
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; //记录新粒子中当前的边数
      for(i=1;i<=(vertice-1);i++)//寻找两个粒子中相同的边
	  {
         for(j=1;j<=(vertice-1);j++)  //找到个体历史最优粒子中与当前粒子第i条边起点相同的位置
		 {
            if(par1_best[j].s==par1[i].s) //找到跳出
				break;
		 }
		 for(;j<=(vertice-1);j++) //个体历史最优粒子中寻找与当前粒子第i条边终点相同的边
		 {
			 if(par1_best[j].s!=par1[i].s)  //起点不同，则不存在相同的边，跳出；
				 break;
			 if(par1_best[j].e==par1[i].e) //找到相同的边
			 {
                sign1[i]=1; //当前粒子中该边标记为1
				sign2[j]=1; //个体历史最优粒子中该边标记位1
				union_set2(par1[i].s,par1[i].e); //合并该边的两个端点为同一组
                new_res1[count_new].s=par1_best[j].s; //将共同边存入new_res1中
				new_res1[count_new].e=par1_best[j].e;
				new_res1[count_new++].line_style=par1_best[j].line_style;
				break;//跳出
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res1[i].s,new_res1[i].e,new_res1[i].line_style);
//	  printf("\nsign1:\n");
 //     for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

	  count_sur1=1; //记录挑完共同边后剩余的边数
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur1[count_sur1].s=par1[i].s;
			  sur1[count_sur1].e=par1[i].e;
			  sur1[count_sur1++].line_style=par1[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur1[count_sur1].s=par1_best[i].s;
			  sur1[count_sur1].e=par1_best[i].e;
			  sur1[count_sur1++].line_style=par1_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur1:%d\n",count_sur1);
//	  for(i=1;i<count_sur1;i++)
//	    printf("%d %d %d\n",sur1[i].s,sur1[i].e,sur1[i].line_style);
//	  printf("\n");

	  while(1)
	  {
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur1-1))+1;
          if(find_set2(sur1[i].s)!=find_set2(sur1[i].e))
		  {
             new_res1[count_new].s=sur1[i].s; 
			 new_res1[count_new].e=sur1[i].e;
			 new_res1[count_new++].line_style=sur1[i].line_style;
			 union_set2(sur1[i].s,sur1[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop[cur].edge[i*3-2]=new_res1[i].s;
          pop[cur].edge[i*3-1]=new_res1[i].e;
          pop[cur].edge[i*3]=new_res1[i].line_style;
	  }

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 

//	  printf("适应度：%lf\n",pop[cur].fit_value);
	}
}

void GetCrossover_rand(int cur)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur1;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
	
//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

    if(c<c1_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1[i].s=pop[cur].edge[i*3-2]; 
		 par1[i].e=pop[cur].edge[i*3-1];
		 par1[i].line_style=pop[cur].edge[i*3];
		 if(par1[i].s>par1[i].e) 
		 {
			 mid=par1[i].s;
			 par1[i].s=par1[i].e;
			 par1[i].e=mid;
			 if(par1[i].line_style==0||par1[i].line_style==1) 
                 par1[i].line_style=!par1[i].line_style;
			 else if(par1[i].line_style==2)
			     par1[i].line_style=3;
			 else if(par1[i].line_style==3)
				 par1[i].line_style=2;
		 }
	  }

	  
  //    printf("par1粒子：\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");
	  InitializeTree();  
	  for(j=1;j<=3*(vertice-1);j++)
			randP.edge[j]=min_tree[j]; 	
	  for(i=1;i<=(vertice-1);i++)//将当前粒子的历史最优解存入结构体中
	  {
         par1_best[i].s=randP.edge[i*3-2];
		 par1_best[i].e=randP.edge[i*3-1];
		 par1_best[i].line_style=randP.edge[i*3];
		 if(par1_best[i].s>par1_best[i].e)//如果起点编号大于终点编号，则交换位置
		 {
			 mid=par1_best[i].s;
			 par1_best[i].s=par1_best[i].e;
			 par1_best[i].e=mid;
			 if(par1_best[i].line_style==0||par1_best[i].line_style==1)//连接方式互换
                 par1_best[i].line_style=!par1_best[i].line_style;
			 else if(par1_best[i].line_style==2)
			     par1_best[i].line_style=3;
			 else if(par1_best[i].line_style==3)
				 par1_best[i].line_style=2;
		 }
	  }
//	  printf("par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");



	  sort(par1+1,par1+vertice,cmpp1); //对粒子的边按照起点由小到大，终点由小到大的顺序排列
      sort(par1_best+1,par1_best+vertice,cmpp1);

	//     printf("排序后par1粒子：\n");
   //   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par1_best粒子：\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");

	  initial2(vertice);
	  for(i=1;i<=(vertice-1);i++)//初始化标记数组，标记哪条边是共同边
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; //记录新粒子中当前的边数
      for(i=1;i<=(vertice-1);i++)//寻找两个粒子中相同的边
	  {
         for(j=1;j<=(vertice-1);j++)  //找到个体历史最优粒子中与当前粒子第i条边起点相同的位置
		 {
            if(par1_best[j].s==par1[i].s) //找到跳出
				break;
		 }
		 for(;j<=(vertice-1);j++) //个体历史最优粒子中寻找与当前粒子第i条边终点相同的边
		 {
			 if(par1_best[j].s!=par1[i].s)  //起点不同，则不存在相同的边，跳出；
				 break;
			 if(par1_best[j].e==par1[i].e) //找到相同的边
			 {
                sign1[i]=1; //当前粒子中该边标记为1
				sign2[j]=1; //个体历史最优粒子中该边标记位1
				union_set2(par1[i].s,par1[i].e); //合并该边的两个端点为同一组
                new_res1[count_new].s=par1_best[j].s; //将共同边存入new_res1中
				new_res1[count_new].e=par1_best[j].e;
				new_res1[count_new++].line_style=par1_best[j].line_style;
				break;//跳出
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res1[i].s,new_res1[i].e,new_res1[i].line_style);
//	  printf("\nsign1:\n");
 //     for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

	  count_sur1=1; //记录挑完共同边后剩余的边数
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur1[count_sur1].s=par1[i].s;
			  sur1[count_sur1].e=par1[i].e;
			  sur1[count_sur1++].line_style=par1[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur1[count_sur1].s=par1_best[i].s;
			  sur1[count_sur1].e=par1_best[i].e;
			  sur1[count_sur1++].line_style=par1_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur1:%d\n",count_sur1);
//	  for(i=1;i<count_sur1;i++)
//	    printf("%d %d %d\n",sur1[i].s,sur1[i].e,sur1[i].line_style);
//	  printf("\n");

	  while(1)
	  {
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur1-1))+1;
          if(find_set2(sur1[i].s)!=find_set2(sur1[i].e))
		  {
             new_res1[count_new].s=sur1[i].s; 
			 new_res1[count_new].e=sur1[i].e;
			 new_res1[count_new++].line_style=sur1[i].line_style;
			 union_set2(sur1[i].s,sur1[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop[cur].edge[i*3-2]=new_res1[i].s;
          pop[cur].edge[i*3-1]=new_res1[i].e;
          pop[cur].edge[i*3]=new_res1[i].line_style;
	  }

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 

//	  printf("适应度：%lf\n",pop[cur].fit_value);
	}
}
