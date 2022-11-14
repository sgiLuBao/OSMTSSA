bool se(struct record2 a, struct record2 b)
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void repeat_select_corner()
{
	int i,j,pp,index_num;
	index_num=vertice;
	times=0;
	while(1)
	{
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(records1[edge[i].index].c[edge[i].c]!=0)
			  break;
	  }
	  if(i==vertice)
	  {
//		  printf("repete_select_point %d times.\n",times);
		  break;
	  }
//	  printf("%d %d\n",times,vertice);
	  corner_select();
	  FILE *fin;
	  fin=fopen("steiner.txt","r");
	    fscanf(fin,"%d",&extra_num);
	  for(i=1;i<=extra_num;i++) 
	    fscanf(fin,"%lf%lf",&graph[vertice+i][0],&graph[vertice+i][1]);
      fclose(fin);
	  
	  for(i=1;i<=(vertice-1);i++)
	  {
		 mres[i].s=edge[i].s;
		 mres[i].e=edge[i].e;
	     mres[i].c=edge[i].c;
		 mres[i].index=edge[i].index;
	  }
      fin=fopen("delete.txt","r");
	    fscanf(fin,"%d",&del_num);
	  for(i=1;i<=del_num;i++)
	  {
        fscanf(fin,"%d %d %d %d",&del[i].s,&del[i].e,&del[i].c,&del[i].index);
		del_index[del[i].s][del[i].e]=del[i].index;
	  }
	  fclose(fin);	  
	  sort(mres+1,mres+vertice,se);
	  sort(del+1,del+del_num+1,se);
      i=1;j=1;pp=1;
	  while(i<=vertice-1) 
	  {
		if(j<=del_num&&mres[i].s==del[j].s&&mres[i].e==del[j].e&&mres[i].c==del[j].c)
		{
            i++;
		    j++;
		}
		else
		{
            edge[pp].s=mres[i].s;
		    edge[pp].e=mres[i].e;
		    edge[pp].c=mres[i].c;
			edge[pp++].index=mres[i++].index;
		}
	  }
	 
	  vertice+=extra_num;
	  fin=fopen("add.txt","r");
		fscanf(fin,"%d",&add_num);	
      for(i=pp;i<pp+add_num;i++)
	  {
         fscanf(fin,"%d %d %d ",&edge[i].s,&edge[i].e,&edge[i].c);
		 edge[i].index=index_num++;
	     judge(edge[i].s,edge[i].e,edge[i].c,edge[i].index); 
	  }
	  fclose(fin);
	  times++;
	}
	for(i=1;i<vertice;i++)
	   edge[i].mark=true;
	count_length();
//	FILE *fout;
//  fout=fopen("point1.txt","w"); 
//   	fprintf(fout,"%d\n",vertice);
//	  for(i=1;i<=vertice;i++)
//		fprintf(fout,"%.0lf %.0lf\n",graph[i][0],graph[i][1]);  
//	fclose(fout);
//	fout=fopen("after.txt","w"); 
//	for(i=1;i<=vertice-1;i++)
//		fprintf(fout,"%d %d %d\n",edge[i].s,edge[i].e,edge[i].c);
//	fclose(fout);
}