void InitializeTree()
{
   int start_point;
   start_point=(int)((rand()/(RAND_MAX+1.0))*vertice)+1;//随机最小生成树的起点
   double lowcost[1010]={0},min;
   int tree[1010][3]={0},adjvex[1010]={0},sign[1010],i,j,index=0;
   for(i=1;i<=vertice;i++) 
   {
	   lowcost[i]=graphw[start_point][i];//每个漏点的最近距离都初始化为与起点的距离
       adjvex[i]=start_point;//每个漏点的最近点都初始化为起点
	   sign[i]=0;
   }
   sign[start_point]=1; //标记起点已经加入最小生成树
   for(i=1;i<vertice;i++)
   {
         min=99999999;
		 for(j=1;j<=vertice;j++)  //取距离最小的边
			 if(lowcost[j]<min&&!sign[j])
			 {
                 index=j;
				 min=lowcost[j];
			 }
		 sign[index]=1; //标记新加入的节点
		 tree[i][1]=adjvex[index]; //存储新加入的边
		 tree[i][2]=index;
		 for(j=1;j<=vertice;j++) //更新距离记录
			 if(lowcost[j]>graphw[j][index]&&!sign[j])
			 {
				 lowcost[j]=graphw[j][index];
				 adjvex[j]=index;
			 }
//	   for(j=1;j<=vertice;j++)
//		   printf("%lf ",lowcost[j]);
//	   printf("\n");
   }
//  printf("start_point:%d\n",start_point);
   for(i=1;i<=(vertice-1);i++) //粒子
   {
	   min_tree[i*3-2]=tree[i][1]; //边起点编号
	   min_tree[i*3-1]=tree[i][2]; //边终点编号
	   min_tree[i*3]=(int)((rand()/(RAND_MAX+1.0))*2); //连接方式
   }
//   for(i=1;i<=3*(vertice-1);i++)
//    printf("%3d",min_tree[i]);
//   printf("\n");
}