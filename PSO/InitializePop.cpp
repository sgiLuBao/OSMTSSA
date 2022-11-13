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
        InitializeTree();  
		for(j=1;j<=3*(vertice-1);j++)
          pop[i].edge[j]=min_tree[j];  
		pop[i].fit_value=Getfitness(); 	
//         printf("%lf\n",pop[i].fit_value);
	}
	printf("\n");
	sort(pop+1,pop+popsize+1,cmp); //sort(数组名,数组名+元素个数,排序函数); 
	for(i=1;i<=popsize;i++)
	{
			//更新全局最优 
			if(i==1) 
			{
				for(j=1;j<=3*(vertice-1);j++)
				  gbest.edge[j]=pop[i].edge[j];
				gbest.fit_value=pop[i].fit_value;
			}
	    for(j=1;j<=3*(vertice-1);j++)
            pbest[i].edge[j]=pop[i].edge[j]; 
        pbest[i].fit_value=pop[i].fit_value;
	}
}
