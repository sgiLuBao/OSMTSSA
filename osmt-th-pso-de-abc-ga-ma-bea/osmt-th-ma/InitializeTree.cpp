void InitializeTree()
{
   int start_point;
   start_point=(int)((rand()/(RAND_MAX+1.0))*vertice)+1;//�����С�����������
   double lowcost[1010]={0},min;
   int tree[1010][3]={0},adjvex[1010]={0},sign[1010],i,j,index=0;
   for(i=1;i<=vertice;i++) 
   {
	   lowcost[i]=graphw[start_point][i];//ÿ��©���������붼��ʼ��Ϊ�����ľ���
       adjvex[i]=start_point;//ÿ��©�������㶼��ʼ��Ϊ���
	   sign[i]=0;
   }
   sign[start_point]=1; //�������Ѿ�������С������
   for(i=1;i<vertice;i++)
   {
         min=99999999;
		 for(j=1;j<=vertice;j++)  //ȡ������С�ı�
			 if(lowcost[j]<min&&!sign[j])
			 {
                 index=j;
				 min=lowcost[j];
			 }
		 sign[index]=1; //����¼���Ľڵ�
		 tree[i][1]=adjvex[index]; //�洢�¼���ı�
		 tree[i][2]=index;
		 for(j=1;j<=vertice;j++) //���¾����¼
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
   for(i=1;i<=(vertice-1);i++) //����
   {
	   min_tree[i*3-2]=tree[i][1]; //�������
	   min_tree[i*3-1]=tree[i][2]; //���յ���
	   min_tree[i*3]=(int)((rand()/(RAND_MAX+1.0))*2); //���ӷ�ʽ
   }
//   for(i=1;i<=3*(vertice-1);i++)
//    printf("%3d",min_tree[i]);
//   printf("\n");
}