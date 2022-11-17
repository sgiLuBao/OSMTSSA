void GenerateGraph()
{
    int i,j=1;
	FILE *fin;
	fin=fopen("input500.txt","r");
	fscanf(fin,"%d",&vertice);
	for(i=1;i<=vertice;i++) //从文件读入漏点坐标到graph数组
		fscanf(fin,"%lf%lf",&graph[i][0],&graph[i][1]);
	fclose(fin);
// printf("%d\n",vertice);
//   for(i=1;i<=vertice;i++)
//   printf("%lf  %lf\n",graph[i][0],graph[i][1]);
    for(i=1;i<=vertice;i++) //生成任意两点之间的距离矩阵
	{
		for(j=1;j<=vertice;j++)
		{
			graphw[i][j]=fabs(graph[i][0]-graph[j][0])+fabs(graph[i][1]-graph[j][1]);
//			printf("%lf ",graphw[i][j]);
		}
// 	  printf("\n");
	}
}