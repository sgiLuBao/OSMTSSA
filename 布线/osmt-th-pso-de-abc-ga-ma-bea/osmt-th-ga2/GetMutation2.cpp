int parent[MAX];
void initial(int n) //ÿ���ڵ������ʼ��Ϊ����
{
	int i;
	for(i=1;i<=n;i++)
		parent[i]=i;
}
int find_set(int x) //�������
{
 int temp;
 if(parent[x]==x) return x;
 else
 {
  temp=parent[x];
  parent[x]=find_set(temp); //ѹ��·��
  return parent[x];
 }
}
void union_set(int a,int b)
{
 int pa,pb;
 pa=find_set(a);
 pb=find_set(b);
 if(pa!=pb) //���û�в���ͬһ����ϲ�
  parent[pb]=pa;
}
void GetMutation(int cur)
{
    double w=rand()/(RAND_MAX+1.0); //�����������С��w_now�����
	double w1=rand()/(RAND_MAX+1.0); //�����������С��w_now�����
	double w2=rand()/(RAND_MAX+1.0); //�����������С��w_now�����
	int p1,p2,m1,j,t,p,q,arr1[1010],arr2[1010],sum1,sum2;
	double f1=0;

//	printf("%lf %lf\n",w,w_now);
	
	if(w<w_now)
	{
	  
//	  printf("��ǰ���ӣ�\n");
//		for(i=1;i<=3*(vertice-1);i++)
//		  printf("%d ",pop[cur].edge[i]);
//	  printf("\n");

	  p1=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;//���ѡȡҪ����ı�
	  p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  while(p1==p2)
         p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  m1=pop[cur].edge[3*p1];//ȡ�������ߵ�ǰ�����ӷ�ʽ
      t=m1;
//	  printf("p1,m1:%d %d\n\n",p1,m1);
	  while(t==m1) //�����һ���ߵ����ӷ�ʽ
	  {
          f1=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f1);
		  if(f1<0.2)
			  m1=2;
		  else if(f1>=0.2&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.8)
			  m1=1;
		  else m1=3;
	  }
	  pop[cur].edge[3*p1]=m1;

//	  printf("�µ�m1��%d\n\n",m1);

	  
	  m1=pop[cur].edge[3*p2];//ȡ�������ߵ�ǰ�����ӷ�ʽ
      t=m1;
//	  printf("p1,m1:%d %d\n\n",p1,m1);
	  while(t==m1) //�����һ���ߵ����ӷ�ʽ
	  {
          f1=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f1);
		  if(f1<0.2)
			  m1=2;
		  else if(f1>=0.2&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.8)
			  m1=1;
		  else m1=3;
	  }
	  pop[cur].edge[3*p2]=m1;
  
//	  printf("�µ�m1��%d\n\n",m1);
	}
	/////�޸�
	if(w1<w_now)
	{
	  
//	  printf("��ǰ���ӣ�\n");
//		for(i=1;i<=3*(vertice-1);i++)
//		  printf("%d ",pop[cur].edge[i]);
//	  printf("\n");

	  p1=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;//���ѡȡҪ����ı�
	  p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  while(p1==p2)
         p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;

	  initial(vertice);
      for(j=1;j<=(vertice-1);j++) //�ϲ�����һ��Ķ˵�
	  {
            if(j==p1) continue; //��ѡ�б���ĶϿ��߲��ϲ�
		    p=pop[cur].edge[3*j-2];
			q=pop[cur].edge[3*j-1];
			union_set(p,q);
	  }

//	  for(i=1;i<=vertice;i++)
//	   printf("%d ",find_set(i));
//	  printf("\n");

	  for(j=1;j<=vertice;j++)
	  {
		  if(parent[j]==j) //��Ϊֻ�������飬����ֻ��ҪѰ�ҵ�һ���鼴��
		  {
			  p=j;
			  break;
		  }
	  }

//	  printf("%d\n",p);

	  sum1=1;sum2=1;
	  for(j=1;j<=vertice;j++) //����ֵ���������
	  {
		  if(find_set(j)==p)
			  arr1[sum1++]=j;
		  else arr2[sum2++]=j;
	  }
//	  for(i=1;i<sum1;i++)
//		  printf("%d ",arr1[i]);
//	  printf("\n");
//	  for(i=1;i<sum2;i++)
//		  printf("%d ",arr2[i]);
//	  printf("\n");

      p=(int)((rand()/(RAND_MAX+1.0))*(sum1-1))+1;
	  q=(int)((rand()/(RAND_MAX+1.0))*(sum2-1))+1;

	//  printf("%d %d\n",p,q);

	  pop[cur].edge[p1*3-2]=arr1[p];
	  pop[cur].edge[p1*3-1]=arr2[q];

	  initial(vertice);
      for(j=1;j<=(vertice-1);j++) //�ϲ�����һ��Ķ˵�
	  {
            if(j==p2) continue; //��ѡ�б���ĶϿ��߲��ϲ�
		    p=pop[cur].edge[3*j-2];
			q=pop[cur].edge[3*j-1];
			union_set(p,q);
	  }
      for(j=1;j<=vertice;j++)
	  {
		  if(parent[j]==j) //��Ϊֻ�������飬����ֻ��ҪѰ�ҵ�һ���鼴��
		  {
			  p=j;
			  break;
		  }
	  }
	  sum1=1;sum2=1;
	  for(j=1;j<=vertice;j++) //����ֵ���������
	  {
		  if(find_set(j)==p)
			  arr1[sum1++]=j;
		  else arr2[sum2++]=j;
	  }
	  p=(int)((rand()/(RAND_MAX+1.0))*(sum1-1))+1;
	  q=(int)((rand()/(RAND_MAX+1.0))*(sum2-1))+1;
	  pop[cur].edge[p2*3-2]=arr1[p];
	  pop[cur].edge[p2*3-1]=arr2[q];
      for(j=1;j<=3*(vertice-1);j++)
		  min_tree[j]=pop[cur].edge[j];
	  pop[cur].fit_value=Getfitness(); 
//	  printf("��Ӧ��ֵ��%lf\n", pop[cur].fit_value);
	}
//	 for(j=1;j<=3*(vertice-1);j++)
//		 printf("%3d",pop[cur].edge[j]);
//	 printf("\n");
//	 printf("%lf\n",pop[cur].fit_value);
}