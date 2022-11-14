void print_result()
{
	int i,sum=0;
	FILE *fout;
	fout=fopen("point.txt","w");
       fprintf(fout,"%d\n",vertice);
    for(i=1;;i++)
	{
	   if(graph[i][2])
	   {
	     fprintf(fout,"%.0lf %.0lf\n",graph[i][0],graph[i][1]); 
		 sum++;
	   }
	   if(sum==vertice) break;
	}
	fclose(fout);
	printf("length:%lf\n",final_len);
	sum=0;
	fout=fopen("result.txt","w");
	for(i=1;;i++)
	{
		if(edge[i].mark==true)
		{
		   fprintf(fout,"%d %d %d\n",edge[i].s,edge[i].e,edge[i].c);
	       sum++;
		}
		if(sum==vertice-1) break;
	}
	fprintf(fout,"%lf\n",final_len);
	fclose(fout);
}