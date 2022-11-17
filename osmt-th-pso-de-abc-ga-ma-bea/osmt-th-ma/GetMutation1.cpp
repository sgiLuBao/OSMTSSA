void GetMutation1(int cur)
{
    double w=rand()/(RAND_MAX+1.0); //产生随机数，小于w_now则变异
	int p1,p2,m1,m2,t,j;
	double f1=0,f2=0;
//	printf("%lf %lf\n",w,w_now);
	if(w<w_now)
	{
	  p1=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;//随机选取两个要变异的边
	  p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  while(p1==p2)
		p2=(int)((rand()/(RAND_MAX+1.0))*vertice)+1;
//	  printf("%d %d\n",p1,p2);
	  m1=pop[cur].edge[3*p1];//取出两个边当前的连接方式
	  m2=pop[cur].edge[3*p2];
//	  printf("%d %d\n",m1,m2);
      t=m1;
	  while(t==m1) //变异第一个边
	  {
          f1=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f1);
		  if(f1<0.1)
			  m1=2;
		  else if(f1>0.1&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.9)
			  m1=1;
		  else m1=3;
	  }
	  pop[cur].edge[3*p1]=m1;
      t=m2;
	  while(t==m2) //变异第二个边
	  {
          f2=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f2);
		  if(f2<0.1)
			  m2=2;
		  else if(f2>0.1&&f2<0.5)
			  m2=0;
		  else if(f2>=0.5&&f2<=0.9)
			  m2=1;
		  else m2=3;
	  }
	  pop[cur].edge[3*p2]=m2;
      for(j=1;j<=3*(vertice-1);j++)
		  min_tree[j]=pop[cur].edge[j];
	  pop[cur].fit_value=Getfitness(); 
	}
//	 for(j=1;j<=3*(vertice-1);j++)
//		 printf("%3d",pop[cur].edge[j]);
//	 printf("\n");
//	 printf("%lf\n",pop[cur].fit_value);
}

void GetMutation_GA1(int cur)
{
	double w = rand() / (RAND_MAX + 1.0); //产生随机数，小于w_now则变异
	int p1, p2, m1, m2, t, j;
	double f1 = 0, f2 = 0;
	//	printf("%lf %lf\n",w,w_now);
	if (w<pm)
	{
		p1 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;//随机选取两个要变异的边
		p2 = (int)((rand() / (RAND_MAX + 1.0))*(vertice - 1)) + 1;
		while (p1 == p2)
			p2 = (int)((rand() / (RAND_MAX + 1.0))*vertice) + 1;
		//	  printf("%d %d\n",p1,p2);
		m1 = pop[cur].edge[3 * p1];//取出两个边当前的连接方式
		m2 = pop[cur].edge[3 * p2];
		//	  printf("%d %d\n",m1,m2);
		t = m1;
		while (t == m1) //变异第一个边
		{
			f1 = rand() / (RAND_MAX + 1.0);
			//		  printf("%lf\n",f1);
			if (f1<0.1)
				m1 = 2;
			else if (f1>0.1&&f1<0.5)
				m1 = 0;
			else if (f1 >= 0.5&&f1 <= 0.9)
				m1 = 1;
			else m1 = 3;
		}
		pop[cur].edge[3 * p1] = m1;
		t = m2;
		while (t == m2) //变异第二个边
		{
			f2 = rand() / (RAND_MAX + 1.0);
			//		  printf("%lf\n",f2);
			if (f2<0.1)
				m2 = 2;
			else if (f2>0.1&&f2<0.5)
				m2 = 0;
			else if (f2 >= 0.5&&f2 <= 0.9)
				m2 = 1;
			else m2 = 3;
		}
		pop[cur].edge[3 * p2] = m2;
	}
}