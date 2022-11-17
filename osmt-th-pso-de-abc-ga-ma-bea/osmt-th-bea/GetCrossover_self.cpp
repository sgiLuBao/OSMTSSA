int parent2[MAX];
int parent22[MAX];
void initial2(int n) //ÿ���ڵ������ʼ��Ϊ����
{
	int i;
	for (i = 1; i <= n; i++) {
		parent2[i]=i;
		parent22[i] = i;
	}   
}
int find_set2(int x) //�������
{
 int temp;
 if(parent2[x]==x) return x;
 else
 {
  temp=parent2[x];
  parent2[x]=find_set2(temp); //ѹ��·��
  return parent2[x];
 }
}
void union_set2(int a,int b)
{
  int pa,pb;
  pa=find_set2(a);
  pb=find_set2(b);
  if(pa!=pb) //���û�в���ͬһ����ϲ�
  parent2[pb]=pa;
}
int find_set22(int x) //�������
{
	int temp;
	if (parent22[x] == x) return x;
	else
	{
		temp = parent22[x];
		parent22[x] = find_set22(temp); //ѹ��·��
		return parent22[x];
	}
}
void union_set22(int a, int b)
{
	int pa, pb;
	pa = find_set22(a);
	pb = find_set22(b);
	if (pa != pb) //���û�в���ͬһ����ϲ�
		parent22[pb] = pa;
}
struct tree1 
{
	int s,e;
	int line_style;
}par1[1010], par1_best[1010], sur1[2010], new_res1[1010], sur2[2010]; //��ŵ�ǰ���Ӻ�������ʷ�������ӣ���Ҳ����,sur1��ŷǹ�ͬ��,new_res1��Ž�������ɵ�������
bool cmpp1(struct tree1 a,struct tree1 b) //�������������С�����յ���С�����˳����������
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_self(int cur)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur1;
	c=rand()/(RAND_MAX+1.0); 
//	printf("%lf %lf\n",c,c1_now);
	
//	printf("��ǰ���ӣ�\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

    if(c<c1_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1[i].s=pop[cur].edge[i*3-2]; //����ǰ���Ӵ���ṹ����
		 par1[i].e=pop[cur].edge[i*3-1];
		 par1[i].line_style=pop[cur].edge[i*3];
		 if(par1[i].s>par1[i].e) //�������Ŵ����յ��ţ��򽻻�λ��
		 {
			 mid=par1[i].s;
			 par1[i].s=par1[i].e;
			 par1[i].e=mid;
			 if(par1[i].line_style==0||par1[i].line_style==1) //���ӷ�ʽ����
                 par1[i].line_style=!par1[i].line_style;
			 else if(par1[i].line_style==2)
			     par1[i].line_style=3;
			 else if(par1[i].line_style==3)
				 par1[i].line_style=2;
		 }
	  }

	  
  //    printf("par1���ӣ�\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");

	  for(i=1;i<=(vertice-1);i++)//����ǰ���ӵ���ʷ���Ž����ṹ����
	  {
         par1_best[i].s=pbest[cur].edge[i*3-2];
		 par1_best[i].e=pbest[cur].edge[i*3-1];
		 par1_best[i].line_style=pbest[cur].edge[i*3];
		 if(par1_best[i].s>par1_best[i].e)//�������Ŵ����յ��ţ��򽻻�λ��
		 {
			 mid=par1_best[i].s;
			 par1_best[i].s=par1_best[i].e;
			 par1_best[i].e=mid;
			 if(par1_best[i].line_style==0||par1_best[i].line_style==1)//���ӷ�ʽ����
                 par1_best[i].line_style=!par1_best[i].line_style;
			 else if(par1_best[i].line_style==2)
			     par1_best[i].line_style=3;
			 else if(par1_best[i].line_style==3)
				 par1_best[i].line_style=2;
		 }
	  }
//	  printf("par1_best���ӣ�\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");



	  sort(par1+1,par1+vertice,cmpp1); //�����ӵı߰��������С�����յ���С�����˳������
      sort(par1_best+1,par1_best+vertice,cmpp1);

	//     printf("�����par1���ӣ�\n");
   //   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
//	  printf("\n");
//	  	  printf("�����par1_best���ӣ�\n");
 //for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
//	  printf("\n");

	  initial2(vertice);
	  for(i=1;i<=(vertice-1);i++)//��ʼ��������飬����������ǹ�ͬ��
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; //��¼�������е�ǰ�ı���
      for(i=1;i<=(vertice-1);i++)//Ѱ��������������ͬ�ı�
	  {
         for(j=1;j<=(vertice-1);j++)  //�ҵ�������ʷ�����������뵱ǰ���ӵ�i���������ͬ��λ��
		 {
            if(par1_best[j].s==par1[i].s) //�ҵ�����
				break;
		 }
		 for(;j<=(vertice-1);j++) //������ʷ����������Ѱ���뵱ǰ���ӵ�i�����յ���ͬ�ı�
		 {
			 if(par1_best[j].s!=par1[i].s)  //��㲻ͬ���򲻴�����ͬ�ıߣ�������
				 break;
			 if(par1_best[j].e==par1[i].e) //�ҵ���ͬ�ı�
			 {
                sign1[i]=1; //��ǰ�����иñ߱��Ϊ1
				sign2[j]=1; //������ʷ���������иñ߱��λ1
				union_set2(par1[i].s,par1[i].e); //�ϲ��ñߵ������˵�Ϊͬһ��
                new_res1[count_new].s=par1_best[j].s; //����ͬ�ߴ���new_res1��
				new_res1[count_new].e=par1_best[j].e;
				new_res1[count_new++].line_style=par1_best[j].line_style;
				break;//����
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res1[i].s,new_res1[i].e,new_res1[i].line_style);
//	  printf("\nsign1:\n");
 //     for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

	  count_sur1=1; //��¼���깲ͬ�ߺ�ʣ��ı���
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur1[count_sur1].s=par1[i].s;
			  sur1[count_sur1].e=par1[i].e;
			  sur1[count_sur1++].line_style=par1[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur1[count_sur1].s=par1_best[i].s;
			  sur1[count_sur1].e=par1_best[i].e;
			  sur1[count_sur1++].line_style=par1_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur1:%d\n",count_sur1);
//	  for(i=1;i<count_sur1;i++)
//	    printf("%d %d %d\n",sur1[i].s,sur1[i].e,sur1[i].line_style);
//	  printf("\n");

	  while(1)
	  {
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur1-1))+1;
          if(find_set2(sur1[i].s)!=find_set2(sur1[i].e))
		  {
             new_res1[count_new].s=sur1[i].s; 
			 new_res1[count_new].e=sur1[i].e;
			 new_res1[count_new++].line_style=sur1[i].line_style;
			 union_set2(sur1[i].s,sur1[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop[cur].edge[i*3-2]=new_res1[i].s;
          pop[cur].edge[i*3-1]=new_res1[i].e;
          pop[cur].edge[i*3]=new_res1[i].line_style;
	  }

//	  	printf("�µĵ�ǰ���ӣ�\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop[cur].edge[i];
	  pop[cur].fit_value=Getfitness(); 

//	  printf("��Ӧ�ȣ�%lf\n",pop[cur].fit_value);
	}
}

void GetCrossover_BEA(int cur1, int cur2)
{
	double c;
	int i, j, mid = 0, sign1[1010], sign2[1010], count_new, count_sur1, count_new1, count_new2, count_sur2;
	c = rand() / (RAND_MAX + 1.0);
	//	printf("%lf %lf\n",c,c1_now);

	//	printf("��ǰ���ӣ�\n");
	//	for(i=1;i<=3*(vertice-1);i++)
	//		printf("%d ",pop[cur].edge[i]);
	//	printf("\n");

	if (c<cm)
	{
		for (i = 1; i <= (vertice - 1); i++)
		{
			par1[i].s = pop[cur1].edge[i * 3 - 2]; //����ǰ���Ӵ���ṹ����
			par1[i].e = pop[cur1].edge[i * 3 - 1];
			par1[i].line_style = pop[cur1].edge[i * 3];
			if (par1[i].s>par1[i].e) //�������Ŵ����յ��ţ��򽻻�λ��
			{
				mid = par1[i].s;
				par1[i].s = par1[i].e;
				par1[i].e = mid;
				if (par1[i].line_style == 0 || par1[i].line_style == 1) //���ӷ�ʽ����
					par1[i].line_style = !par1[i].line_style;
				else if (par1[i].line_style == 2)
					par1[i].line_style = 3;
				else if (par1[i].line_style == 3)
					par1[i].line_style = 2;
			}
		}


		//    printf("par1���ӣ�\n");
		//    for(i=1;i<=(vertice-1);i++)
		//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
		//	  printf("\n");

		for (i = 1; i <= (vertice - 1); i++)//����ǰ���ӵ���ʷ���Ž����ṹ����
		{
			par1_best[i].s = pop[cur2].edge[i * 3 - 2];
			par1_best[i].e = pop[cur2].edge[i * 3 - 1];
			par1_best[i].line_style = pop[cur2].edge[i * 3];
			if (par1_best[i].s>par1_best[i].e)//�������Ŵ����յ��ţ��򽻻�λ��
			{
				mid = par1_best[i].s;
				par1_best[i].s = par1_best[i].e;
				par1_best[i].e = mid;
				if (par1_best[i].line_style == 0 || par1_best[i].line_style == 1)//���ӷ�ʽ����
					par1_best[i].line_style = !par1_best[i].line_style;
				else if (par1_best[i].line_style == 2)
					par1_best[i].line_style = 3;
				else if (par1_best[i].line_style == 3)
					par1_best[i].line_style = 2;
			}
		}
		//	  printf("par1_best���ӣ�\n");
		//for(i=1;i<=(vertice-1);i++)
		//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
		//	  printf("\n");



		sort(par1 + 1, par1 + vertice, cmpp1); //�����ӵı߰��������С�����յ���С�����˳������
		sort(par1_best + 1, par1_best + vertice, cmpp1);

		//     printf("�����par1���ӣ�\n");
		//   for(i=1;i<=(vertice-1);i++)
		//	    printf("%d %d %d\n",par1[i].s,par1[i].e,par1[i].line_style);
		//	  printf("\n");
		//	  	  printf("�����par1_best���ӣ�\n");
		//for(i=1;i<=(vertice-1);i++)
		//	    printf("%d %d %d\n",par1_best[i].s,par1_best[i].e,par1_best[i].line_style);
		//	  printf("\n");

		initial2(vertice);
		for (i = 1; i <= (vertice - 1); i++)//��ʼ��������飬����������ǹ�ͬ��
		{
			sign1[i] = 0;
			sign2[i] = 0;
		}
		count_new = 1; //��¼�������е�ǰ�ı���
		for (i = 1; i <= (vertice - 1); i++)//Ѱ��������������ͬ�ı�
		{
			for (j = 1; j <= (vertice - 1); j++)  //�ҵ�������ʷ�����������뵱ǰ���ӵ�i���������ͬ��λ��
			{
				if (par1_best[j].s == par1[i].s) //�ҵ�����
					break;
			}
			for (; j <= (vertice - 1); j++) //������ʷ����������Ѱ���뵱ǰ���ӵ�i�����յ���ͬ�ı�
			{
				if (par1_best[j].s != par1[i].s)  //��㲻ͬ���򲻴�����ͬ�ıߣ�������
					break;
				if (par1_best[j].e == par1[i].e) //�ҵ���ͬ�ı�
				{
					sign1[i] = 1; //��ǰ�����иñ߱��Ϊ1
					sign2[j] = 1; //������ʷ���������иñ߱��λ1
					union_set2(par1[i].s, par1[i].e); //�ϲ��ñߵ������˵�Ϊͬһ��
					union_set22(par1[i].s, par1[i].e);
					new_res1[count_new].s = par1_best[j].s; //����ͬ�ߴ���new_res1��
					new_res1[count_new].e = par1_best[j].e;
					new_res1[count_new++].line_style = par1_best[j].line_style;
					break;//����
				}
			}
		}

		//	  printf("count_new:%d\n",count_new);
		//	  for(i=1;i<count_new;i++)
		//	    printf("%d %d %d\n",new_res1[i].s,new_res1[i].e,new_res1[i].line_style);
		//	  printf("\nsign1:\n");
		//     for(i=1;i<=(vertice-1);i++)
		//	    printf("%d ",sign1[i]);
		//	  printf("\nsign2:\n");
		//    for(i=1;i<=(vertice-1);i++)
		//	    printf("%d ",sign2[i]);
		//	  printf("\n");

		count_sur1 = 1; //��¼���깲ͬ�ߺ�ʣ��ı���
		count_sur2 = 1;
		for (i = 1; i <= (vertice - 1); i++)
		{
			if (!sign1[i])
			{
				sur1[count_sur1].s = par1[i].s;
				sur1[count_sur1].e = par1[i].e;
				sur1[count_sur1++].line_style = par1[i].line_style;
				sur2[count_sur2].s = par1[i].s;
				sur2[count_sur2].e = par1[i].e;
				sur2[count_sur2++].line_style = par1[i].line_style;
			}
			if (!sign2[i])
			{
				sur1[count_sur1].s = par1_best[i].s;
				sur1[count_sur1].e = par1_best[i].e;
				sur1[count_sur1++].line_style = par1_best[i].line_style;
				sur2[count_sur2].s = par1_best[i].s;
				sur2[count_sur2].e = par1_best[i].e;
				sur2[count_sur2++].line_style = par1_best[i].line_style;
			}
		}

		//	  printf("count_sur1:%d\n",count_sur1);
		//	  for(i=1;i<count_sur1;i++)
		//	    printf("%d %d %d\n",sur1[i].s,sur1[i].e,sur1[i].line_style);
		//	  printf("\n");
		count_new1 = count_new;
		count_new2 = count_new;
		while (1)
		{
			if (count_new1 == vertice) break;
			i = (int)((rand() / (RAND_MAX + 1.0))*(count_sur1 - 1)) + 1;
			if (find_set2(sur1[i].s) != find_set2(sur1[i].e))
			{
				new_res1[count_new1].s = sur1[i].s;
				new_res1[count_new1].e = sur1[i].e;
				new_res1[count_new1++].line_style = sur1[i].line_style;
				union_set2(sur1[i].s, sur1[i].e);
			}
		}
		for (i = 1; i <= (vertice - 1); i++)
		{
			pop[cur1].edge[i * 3 - 2] = new_res1[i].s;
			pop[cur1].edge[i * 3 - 1] = new_res1[i].e;
			pop[cur1].edge[i * 3] = new_res1[i].line_style;
		}
		while (1)
		{
			if (count_new2 == vertice) break;
			i = (int)((rand() / (RAND_MAX + 1.0))*(count_sur2 - 1)) + 1;
			if (find_set22(sur2[i].s) != find_set22(sur2[i].e))
			{
				new_res1[count_new2].s = sur2[i].s;
				new_res1[count_new2].e = sur2[i].e;
				new_res1[count_new2++].line_style = sur2[i].line_style;
				union_set22(sur2[i].s, sur2[i].e);
			}
		}
		for (i = 1; i <= (vertice - 1); i++)
		{
			pop[cur2].edge[i * 3 - 2] = new_res1[i].s;
			pop[cur2].edge[i * 3 - 1] = new_res1[i].e;
			pop[cur2].edge[i * 3] = new_res1[i].line_style;
		}
	}
}