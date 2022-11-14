int parent1[MAX];
void initial1(int n) //每个节点的组别初始化为自身
{
	int i;
	for(i=1;i<=n;i++)
	   parent1[i]=i;
}
int find_set1(int x) //查找组别
{
 int temp;
 if(parent1[x]==x) return x;
 else
 {
  temp=parent1[x];
  parent1[x]=find_set1(temp); //压缩路径
  return parent1[x];
 }
}
void union_set1(int a,int b)
{
  int pa,pb;
  pa=find_set1(a);
  pb=find_set1(b);
  if(pa!=pb) //如果没有并到同一组则合并
  parent1[pb]=pa;
}
struct tree 
{
	int s,e;
	int line_style;
}par[1010],par_best[1010],sur[2010],new_res[1010];//存放当前粒子和自身历史最优粒子，便也排序,sur存放非共同边,new_res存放交叉后生成的新粒子
bool cmpp(struct tree a,struct tree b) //按照粒子起点由小到大，终点由小到大的顺序排列粒子
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
         par[i].s=pop[cur].edge[i*3-2]; //将当前粒子存入结构体中
		 par[i].e=pop[cur].edge[i*3-1];
		 par[i].line_style=pop[cur].edge[i*3];
		 if(par[i].s>par[i].e) //如果起点编号大于终点编号，则交换位置
		 {
			 mid=par[i].s;
			 par[i].s=par[i].e;
			 par[i].e=mid;
			 if(par[i].line_style==0||par[i].line_style==1) //连接方式互换
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

	  for(i=1;i<=(vertice-1);i++)//将当前粒子的历史最优解存入结构体中
	  {
         par_best[i].s=gbest.edge[i*3-2];
		 par_best[i].e=gbest.edge[i*3-1];
		 par_best[i].line_style=gbest.edge[i*3];
		 if(par_best[i].s>par_best[i].e)//如果起点编号大于终点编号，则交换位置
		 {
			 mid=par_best[i].s;
			 par_best[i].s=par_best[i].e;
			 par_best[i].e=mid;
			 if(par_best[i].line_style==0||par_best[i].line_style==1)//连接方式互换
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



	  sort(par+1,par+vertice,cmpp); //对粒子的边按照起点由小到大，终点由小到大的顺序排列
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
            if(par_best[j].s==par[i].s) //找到跳出
				break;
		 }
		 for(;j<=(vertice-1);j++) //个体历史最优粒子中寻找与当前粒子第i条边终点相同的边
		 {
			 if(par_best[j].s!=par[i].s)  //起点不同，则不存在相同的边，跳出；
				 break;
			 if(par_best[j].e==par[i].e) //找到相同的边
			 {
                sign1[i]=1; //当前粒子中该边标记为1
				sign2[j]=1; //个体历史最优粒子中该边标记位1
				union_set1(par[i].s,par[i].e); //合并该边的两个端点为同一组
                new_res[count_new].s=par_best[j].s; //将共同边存入new_res中
				new_res[count_new].e=par_best[j].e;
				new_res[count_new++].line_style=par_best[j].line_style;
				break;//跳出
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

	  count_sur=1; //记录挑完共同边后剩余的边数
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

//	  printf("适应度：%lf\n",pop[cur].fit_value);
	}
}