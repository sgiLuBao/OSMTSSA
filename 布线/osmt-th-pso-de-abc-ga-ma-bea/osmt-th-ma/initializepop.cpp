bool cmp(struct pop a,struct pop b)
{
	if(a.fit_value<b.fit_value)
	  return true;
	else 
	  return false ;
 }
void LocalSearch(int cur) {
	int i, j, bestvalue, minfit, edge_type, nowfit;
	int p1, p2, mid;
	p1 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;
	p2 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;
	if (p1 > p2) {
		mid = p1;
		p1 = p2;
		p2 = mid;
	}
	if (p2 - p1 > 5) {
		p2 = p1 + 5;
	}
	for (i = 1; i <= 3 * (vertice - 1); i++) {
		min_tree[i] = pop[cur].edge[i];
	}
	minfit = Getfitness();
	pop[cur].fit_value = minfit;
	for (i = p1; i <= p2; i++) {
		edge_type = pop[cur].edge[i * 3];
		for (j = 0; j < 4; j++) {
			if (j != edge_type) {
				min_tree[i * 3] = j;
				nowfit = Getfitness();
				if (nowfit < minfit) {
					pop[cur].edge[i * 3] = j;
					minfit = nowfit;
					pop[cur].fit_value = minfit;
				}
			}
		}
		min_tree[i * 3] = pop[cur].edge[i * 3];
	}
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
		}
		pop[i].fit_value = Getfitness(); //计算当前粒子的适应度
	}

	//local search
	for (i = 1; i <= popsize; i++) {
		LocalSearch(i);
	}

	sort(pop + 1, pop + popsize + 1, cmp); //对初始种群按照适应度值递增的顺序排列
	for (i = 1; i <= (vertice - 1) * 3; i++) {
		gbest.edge[i] = pop[1].edge[i];
	}
	gbest.fit_value = pop[1].fit_value;
}