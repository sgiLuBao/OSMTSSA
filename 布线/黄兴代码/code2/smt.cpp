void smt()
{
	int i,k,t;
	for(i=1;i<=vertice-1;i++)
	{
		if(records1[i].c[0]==0)
		{
			edge[i].c=0;
			continue;
		}
		if(records1[i].c[1]==0)
		{
            edge[i].c=1;
			continue;
		}
		if(records1[i].c[2]==0||records1[i].c[3]==0)
		{
			if(records1[i].semiperimeter[0]<records1[i].semiperimeter[1])
				edge[i].c=0;
			else edge[i].c=1;
		}
		else
		{
           t=records1[i].semiperimeter[0];
		   edge[i].c=0;
		   for(k=1;k<=3;k++)
		   {
			   if(records1[i].semiperimeter[k]<t)
			   {
				   t=records1[i].semiperimeter[k];
				   edge[i].c=k;
			   }
		   }
		}
	}
//	FILE *fout;
//	fout=fopen("smt.txt","w");
//	for(i=1;i<=(vertice-1);i++)
//		fprintf(fout,"%d %d %d\n",edge[i].s,edge[i].e,edge[i].c);
//	fclose(fout);
}