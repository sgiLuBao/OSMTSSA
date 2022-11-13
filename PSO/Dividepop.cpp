void Dividepop(){
	int j;
	for(int i=1;i<=popsize;i++)
	{
			//更新发现者
			if(i<=Np) 
			{
				if(i==1){
					for(j=1;j<=3*(vertice-1);j++)
					  NPbest.edge[j]=pop[i].edge[j];
					NPbest.fit_value=pop[i].fit_value;
				}
				for(j=1;j<=3*(vertice-1);j++)
				  NP[i].edge[j]=pop[i].edge[j];
				NP[i].fit_value=pop[i].fit_value;
			}
			else{
				for(j=1;j<=3*(vertice-1);j++)
            		NJ[i-Np].edge[j]=pop[i].edge[j]; 
        		NJ[i-Np].fit_value=pop[i].fit_value;
			}
	}
}
