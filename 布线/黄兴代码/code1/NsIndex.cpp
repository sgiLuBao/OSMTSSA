void NsIndex(){
	int i=0,j,r;
	srand((int)time(0));   //用当前时间作为随机种子 
	while(i<Ns)
	{
		r=rand() % popsize + 1;  //生成一个1-popsize的随机数 
		for(j=i;j>=0;j--)
		{
			if(r==NsIdx[j])     //与之前已存的随机数比较 
				break;
		}
		if(j<0)             //没有重复即保存到数组中 
		{
			NsIdx[i]=r;
			i++;
		}
	}
	for(i=0;i<Ns;i++) {
		for(j=1;j<=3*(vertice-1);j++)
			  NS[i+1].edge[j]=pop[NsIdx[i]].edge[j];
        NS[i+1].fit_value=pop[NsIdx[i]].fit_value;		
	}
}
