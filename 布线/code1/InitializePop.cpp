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
        int source=-1;
		source = InitializeTree();
		pop[i].source = source; 
		for(j=1;j<=3*(vertice-1);j++)
          pop[i].edge[j]=min_tree[j];  
		pop[i].fit_value=Getfitness(); 
		pop[i].maxPL=GetMaxPL();	
//         printf("%lf\n",pop[i].fit_value);
	}
	printf("\n");
	sort(pop+1,pop+popsize+1,cmp); 
	for(i=1;i<=popsize;i++)
	{
		
			if(i==1) 
			{
				for(j=1;j<=3*(vertice-1);j++)
				  gbest.edge[j]=pop[i].edge[j];
				gbest.source=pop[i].source;
				gbest.fit_value=pop[i].fit_value;
				gbest.maxPL=pop[i].maxPL;
			}
	    for(j=1;j<=3*(vertice-1);j++)
            pbest[i].edge[j]=pop[i].edge[j]; 
        pbest[i].fit_value=pop[i].fit_value;
        pbest[i].source=pop[i].source;
       	pbest[i].maxPL=pop[i].maxPL;
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
//	FILE *fout;
//	fout=fopen("result.txt","w");
//	for(i=1;i<=popsize;i++)
//	{
//		for(j=1;j<=3*(vertice-1);j++)
//			fprintf(fout,"%d ",pop[i].edge[j]);
//		fprintf(fout,"\n");
//	}
}
