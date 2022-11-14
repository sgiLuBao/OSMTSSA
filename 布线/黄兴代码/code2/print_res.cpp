void print_res()
{
	int i;
    final_len=count_length();
	printf("%lf\n",final_len);
	FILE *fout;
	fout=fopen("point.txt","w"); //输出最终所有点到point.txt中
       fprintf(fout,"%d\n",vertice);
    for(i=1;i<=vertice;i++)
	   fprintf(fout,"%.0lf %.0lf\n",graph[i][0],graph[i][1]);  
	fclose(fout);
	fout=fopen("result.txt","w");
	for(i=1;i<=(vertice-1);i++)
		fprintf(fout,"%d %d %d\n",edge[i][0],edge[i][1],edge[i][2]);
	fprintf(fout,"%lf\n",final_len);
	fclose(fout);
}