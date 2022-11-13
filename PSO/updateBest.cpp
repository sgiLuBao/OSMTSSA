void updateBest(){
	int i,j;
	for(i=1;i<=popsize;i++){
		if(pop[i].fit_value<pbest[i].fit_value)
		{
			for(j=1;j<=3*(vertice-1);j++)
				pbest[i].edge[j]=pop[i].edge[j];
	        pbest[i].fit_value=pop[i].fit_value;
		}
		if(pbest[i].fit_value<min_fitness)
		{
			for(j=1;j<=3*(vertice-1);j++)
	    	    gbest.edge[j]=pbest[i].edge[j];
	        gbest.fit_value=pbest[i].fit_value;
	        min_fitness=pbest[i].fit_value;
		}
		if(pbest[i].fit_value>worst_fitness){
			for(j=1;j<=3*(vertice-1);j++)
	    	    gWorst.edge[j]=pbest[i].edge[j];
	        gWorst.fit_value=pbest[i].fit_value;
	        worst_fitness=pbest[i].fit_value;
		}
}
}
