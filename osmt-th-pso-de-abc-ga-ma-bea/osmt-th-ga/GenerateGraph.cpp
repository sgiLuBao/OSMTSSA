void GenerateGraph()
{
    int i,j=1;
	FILE *fin;
	fin=fopen("input500.txt","r");
	fscanf(fin,"%d",&vertice);
	for(i=1;i<=vertice;i++) //���ļ�����©�����굽graph����
		fscanf(fin,"%lf%lf",&graph[i][0],&graph[i][1]);
	fclose(fin);
// printf("%d\n",vertice);
//   for(i=1;i<=vertice;i++)
//   printf("%lf  %lf\n",graph[i][0],graph[i][1]);
    for(i=1;i<=vertice;i++) //������������֮��ľ������
	{
		for(j=1;j<=vertice;j++)
		{
			graphw[i][j]=fabs(graph[i][0]-graph[j][0])+fabs(graph[i][1]-graph[j][1]);
//			printf("%lf ",graphw[i][j]);
		}
// 	  printf("\n");
	}
}