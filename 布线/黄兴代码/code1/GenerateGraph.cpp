void GenerateGraph()
{
    int i,j=1;
	FILE *fin;
	fin=fopen("rc02.txt","r");
	fscanf(fin,"%d",&vertice);//顶点个数（即引脚个数），读取第一行 
	for(i=1;i<=vertice;i++) 
		fscanf(fin,"%lf%lf",&graph[i][0],&graph[i][1]);
    fscanf(fin,"%d",&barr_num);//障碍物个数（即矩形个数）
	for(i=1;i<=barr_num;i++)
        fscanf(fin,"%lf%lf%lf%lf",&barr[i][0],&barr[i][1],&barr[i][2],&barr[i][3]);
	fclose(fin);
	strict_barr();
//   for(i=1;i<=vertice;i++)
//   printf("%lf  %lf\n",graph[i][0],graph[i][1]);
    for(i=1;i<=vertice;i++) 
	{
		for(j=1;j<=vertice;j++)
		{
			graphw[i][j]=fabs(graph[i][0]-graph[j][0])+fabs(graph[i][1]-graph[j][1]);//顶点i与顶点j之间欧几里得距离 
//			printf("%lf ",graphw[i][j]);
		}
// 	  printf("\n");
	}
}
