void GetCrossover_self1(int cur)
{
    double c;
	int i,r1,r2,mid=0;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
    if(c<c1_now)
	{
	  r1=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;//随机选取两个边[1—vertice-1]
	  r2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  while(r1==r2)
		r2=(int)((rand()/(RAND_MAX+1.0))*vertice)+1;
      if(r1>r2)
      {
		  mid=r1;
		  r1=r2;
		  r2=mid;
	  }
//	  printf("%d %d\n",r1,r2);
	  for(i=r1;i<=r2;i++)
         pop[cur].edge[i*3]=pbest[cur].edge[i*3];
	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 
	}

//	for(i=1;i<=3*(vertice-1);i++)
//		 printf("%3d",pop[cur].edge[i]);
//	 printf("\n");
//	 printf("%lf\n",pop[cur].fit_value);
}

void GetCrossover_GA1(int cur1,int cur2)
{
	double c;
	int i, r1, r2, mid = 0,temp;
	c = rand() / (RAND_MAX + 1.0);
	if (c<cm)
	{
		r1 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;//随机选取两个边[1—vertice-1]
		r2 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;
		while (r1 == r2)
			r2 = (int)((rand() / (RAND_MAX + 1.0))*vertice) + 1;
		if (r1>r2)
		{
			mid = r1;
			r1 = r2;
			r2 = mid;
		}
		for (i = r1; i <= r2; i++) {
			temp = pop[cur1].edge[i * 3];
			pop[cur1].edge[i * 3] = pop[cur2].edge[i * 3];
			pop[cur2].edge[i * 3] = temp;
		}
	}
}