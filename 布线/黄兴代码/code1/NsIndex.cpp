void NsIndex(){
	int i=0,j,r;
	srand((int)time(0));   //�õ�ǰʱ����Ϊ������� 
	while(i<Ns)
	{
		r=rand() % popsize + 1;  //����һ��1-popsize������� 
		for(j=i;j>=0;j--)
		{
			if(r==NsIdx[j])     //��֮ǰ�Ѵ��������Ƚ� 
				break;
		}
		if(j<0)             //û���ظ������浽������ 
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
