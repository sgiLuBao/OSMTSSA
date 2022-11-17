bool cmp(struct pop a,struct pop b)
{
	if(a.fit_value<b.fit_value)
	  return true;
	else 
	  return false ;
 }
void InitializePop()
{
	int i,j;
	for(i=1;i<=popsize;i++)
	{
        InitializeTree();  //随机生成popsize个粒子
		for(j=1;j<=3*(vertice-1);j++)
          pop[i].edge[j]=min_tree[j];  //存入种群数组中
		pop[i].fit_value=Getfitness(); //计算当前粒子的适应度
		//自适应学习因子
		fave = fave + pop[i].fit_value;
		if (pop[i].fit_value<ffmin)
			ffmin = pop[i].fit_value;
		if (pop[i].fit_value>ffmax)
			ffmax = pop[i].fit_value;
  //       printf("%lf\n",pop[i].fit_value);
	}
	fave = fave/popsize;
	printf("\n");
	sort(pop+1,pop+popsize+1,cmp); //对初始种群按照适应度值递增的顺序排列
	for(i=1;i<=popsize;i++)
	{
		for(j=1;j<=3*(vertice-1);j++)
		{
			if(i==1) //取排列后的第一个粒子付给全局最优
			{
				gbest.edge[j]=pop[i].edge[j];
				gbest.fit_value=pop[i].fit_value;
			}
            pbest[i].edge[j]=pop[i].edge[j]; //每个粒子的个体最优初始化为自身
		}
        pbest[i].fit_value=pop[i].fit_value;
	}
//	for(i=1;i<=popsize;i++)
//	{
//		for(j=1;j<=3*(vertice-1);j++)
//			printf("%3d",pop[i].edge[j]);
//	printf("\n");
//	printf("%lf\n\n",pop[i].fit_value);
//	}
//	 for(j=1;j<=3*(vertice-1);j++)
//		  printf("%3d",gbest.edge[j]);
//	 	printf("\n");
//	printf("%lf\n\n",gbest.fit_value);
//	}
//	for(j=1;j<=3*(vertice-1);j++)
//		printf("%3d",gbest.edge[j]);
//	printf("\n");
//	printf("%lf\n\n",gbest.fit_value);
//	for(i=1;i<=popsize;i++)
//	{
//		for(j=1;j<=3*(vertice-1);j++)
//			printf("%3d",pbest[i].edge[j]);
//	printf("\n");
//	printf("%lf\n\n",pbest[i].fit_value);
//	}
}
void InitializePop_GA()
{
	int i, j;
	InitializeTree();  //随机生成popsize个粒子
	for (i = 1; i <= popsize; i++)
	{
		for (j = 1; j <= 3 * (vertice - 1); j++) {
			pop[i].edge[j] = min_tree[j];  //存入种群数组中
			pop2[i].edge[j] = min_tree[j];
		}
		pop[i].fit_value = Getfitness(); //计算当前粒子的适应度
		pop2[i].fit_value = pop[i].fit_value;
	}
	sort(pop + 1, pop + popsize + 1, cmp); //对初始种群按照适应度值递增的顺序排列
	for (i = 1; i <= (vertice - 1) * 3; i++) {
		gbest.edge[i] = pop[1].edge[i];
	}
	gbest.fit_value = pop[1].fit_value;
}