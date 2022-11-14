void Initialize()
{
    int i,a,b,c;
	FILE *fin;
	fin=fopen("ind3.txt","r");
	fscanf(fin,"%d",&vertice);
	for(i=1;i<=vertice;i++) 
		fscanf(fin,"%lf%lf",&graph[i][0],&graph[i][1]);
    fscanf(fin,"%d",&barr_num);
	for(i=1;i<=barr_num;i++) 
        fscanf(fin,"%lf%lf%lf%lf",&barr[i][0],&barr[i][1],&barr[i][2],&barr[i][3]);
	fclose(fin);
	ini_v_num=vertice;
    fin=fopen("tt/ind3_t.txt","r");
	i=1;
	while(fscanf(fin,"%d%d%d",&a,&b,&c)!=EOF) 
	{
      triangle[i].a=++a;
      triangle[i].b=++b;
	  triangle[i].c=++c;
	  i++;
	}
	tri_num=i-1; 
//	printf("vertice:%d trangele:%d \n",vertice,tri_num);
}
