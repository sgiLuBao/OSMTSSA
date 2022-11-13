int parent4[MAX];
void initial4(int n) {
	int i;
	for(i=1; i<=n; i++)
		parent4[i]=i;
}
int find_set4(int x) {
	int temp;
	if(parent4[x]==x) return x;
	else {
		temp=parent4[x];
		parent4[x]=find_set4(temp);
		return parent4[x];
	}
}
void union_set4(int a,int b) {
	int pa,pb;
	pa=find_set4(a);
	pb=find_set4(b);
	if(pa!=pb)
		parent4[pb]=pa;
}
struct tree4 {
	int s,e;
	int line_style;
} par4[1010],par4_best[1010],sur4[2020],new_res4[1010];
bool cmpp4(struct tree4 a,struct tree4 b) {
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_self_bydef(int cur) {
	double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur4;
	c=rand()/(RAND_MAX+1.0);
//	printf("%lf %lf\n",c,c1_now);

//	printf("��ǰ���ӣ�\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

	if(c<c1_now) {
		for(i=1; i<=(vertice-1); i++) { //i��
			par4[i].s=pop[cur].edge[i*3-2];
			par4[i].e=pop[cur].edge[i*3-1];
			par4[i].line_style=pop[cur].edge[i*3];
			if(par4[i].s>par4[i].e) { //�����߽��в��������С�ĵ���ǰ����Ŵ�ĵ��ں�
				mid=par4[i].s;
				par4[i].s=par4[i].e;
				par4[i].e=mid;
				if(par4[i].line_style==0||par4[i].line_style==1)
					par4[i].line_style=!par4[i].line_style;
				else if(par4[i].line_style==2)
					par4[i].line_style=3;
				else if(par4[i].line_style==3)
					par4[i].line_style=2;
			}
		}


		//    printf("par4���ӣ�\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4[i].s,par4[i].e,par4[i].line_style);
//	  printf("\n");

		for(i=1; i<=(vertice-1); i++) { //����ǰ���ӵ���ʷ���Ž����ṹ����
			par4_best[i].s=pbest[cur].edge[i*3-2];
			par4_best[i].e=pbest[cur].edge[i*3-1];
			par4_best[i].line_style=pbest[cur].edge[i*3];
			if(par4_best[i].s>par4_best[i].e) { //�������Ŵ����յ��ţ��򽻻�λ��
				mid=par4_best[i].s;
				par4_best[i].s=par4_best[i].e;
				par4_best[i].e=mid;
				if(par4_best[i].line_style==0||par4_best[i].line_style==1)//���ӷ�ʽ����
					par4_best[i].line_style=!par4_best[i].line_style;
				else if(par4_best[i].line_style==2)
					par4_best[i].line_style=3;
				else if(par4_best[i].line_style==3)
					par4_best[i].line_style=2;
			}
		}
//	  printf("par4_best���ӣ�\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4_best[i].s,par4_best[i].e,par4_best[i].line_style);
//	  printf("\n");



		sort(par4+1,par4+vertice,cmpp4); //�����ӵı߰��������С�����յ���С�����˳������
		sort(par4_best+1,par4_best+vertice,cmpp4);

		//     printf("�����par4���ӣ�\n");
		//   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4[i].s,par4[i].e,par4[i].line_style);
//	  printf("\n");
//	  	  printf("�����par4_best���ӣ�\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4_best[i].s,par4_best[i].e,par4_best[i].line_style);
//	  printf("\n");

		initial4(vertice);//���鼯��ʼÿ���Լ����Լ��ĸ���
		for(i=1; i<=(vertice-1); i++) { //��ʼ��������飬����������ǹ�ͬ��
			sign1[i]=0;
			sign2[i]=0;
		}
		count_new=1; //��¼�������е�ǰ�ı���
		for(i=1; i<=(vertice-1); i++) { //Ѱ��������������ͬ�ı�
			for(j=1; j<=(vertice-1); j++) { //�ҵ�������ʷ�����������뵱ǰ���ӵ�i���������ͬ��λ��
				if(par4_best[j].s==par4[i].s) //�ҵ�����
					break;
			}
			for(; j<=(vertice-1); j++) { //������ʷ����������Ѱ���뵱ǰ���ӵ�i�����յ���ͬ�ı�
				if(par4_best[j].s!=par4[i].s)  //��㲻ͬ���򲻴�����ͬ�ıߣ�������
					break;
				if(par4_best[j].e==par4[i].e) { //�ҵ���ͬ�ı�
					sign1[i]=1; //��ǰ�����иñ߱��Ϊ1
					sign2[j]=1; //������ʷ���������иñ߱��λ1
//				union_set4(par4[i].s,par4[i].e); //�ϲ��ñߵ������˵�Ϊͬһ��
					new_res4[count_new].s=par4_best[j].s; //����ͬ�ߴ���new_res4��
					new_res4[count_new].e=par4_best[j].e;
					new_res4[count_new++].line_style=par4_best[j].line_style;
					break;//����
				}
			}
		}

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res4[i].s,new_res4[i].e,new_res4[i].line_style);
//	  printf("\nsign1:\n");
//     for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

		count_sur4=1; //��¼���깲ͬ�ߺ�ʣ��ı���
		for(i=1; i<=(vertice-1); i++) {
			if(!sign1[i]) {
//			  sur4[count_sur4].s=par4[i].s;
//			  sur4[count_sur4].e=par4[i].e;
//			  sur4[count_sur4++].line_style=par4[i].line_style;
				if(find_set4(par4[i].s)!=find_set4(par4[i].e)) {
					union_set4(par4[i].s,par4[i].e);
					sur4[count_sur4].s=par4[i].s;
					sur4[count_sur4].e=par4[i].e;
					sur4[count_sur4++].line_style=par4[i].line_style;
				}
			}
			if(!sign2[i]) {
				if(find_set4(par4_best[i].s)!=find_set4(par4_best[i].e)) {
					union_set4(par4_best[i].s,par4_best[i].e);
					sur4[count_sur4].s=par4_best[i].s;
					sur4[count_sur4].e=par4_best[i].e;
					sur4[count_sur4++].line_style=par4_best[i].line_style;
				}
			}
		}

//	  printf("count_sur4:%d\n",count_sur4);
//	  for(i=1;i<count_sur4;i++)
//	    printf("%d %d %d\n",sur4[i].s,sur4[i].e,sur4[i].line_style);
//	  printf("\n");
		while(1) {
			if(count_sur4==vertice) break;
			i=(int)((rand()/(RAND_MAX+1.0))*(count_new-1))+1;
			if(find_set4(new_res4[i].s)!=find_set4(new_res4[i].e)) {
				sur4[count_sur4].s=new_res4[i].s;
				sur4[count_sur4].e=new_res4[i].e;
				sur4[count_sur4++].line_style=new_res4[i].line_style;
				union_set4(new_res4[i].s,new_res4[i].e);
			}
		}
		for(i=1; i<=(vertice-1); i++) {
			pop[cur].edge[i*3-2]=sur4[i].s;
			pop[cur].edge[i*3-1]=sur4[i].e;
			pop[cur].edge[i*3]=sur4[i].line_style;
		}

//	  	printf("�µĵ�ǰ���ӣ�\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
		for(i=1; i<=3*(vertice-1); i++)
			min_tree[i]=pop[cur].edge[i];
		pop[cur].fit_value=Getfitness();

//	  printf("��Ӧ�ȣ�%lf\n",pop[cur].fit_value);
	}
}
