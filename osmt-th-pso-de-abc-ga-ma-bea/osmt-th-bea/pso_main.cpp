#include"Header.h"
#include"GenerateGraph.cpp"
#include"InitializeTree.cpp"
#include"Getfitness.cpp"
#include"InitializePop.cpp"
#include"GetMutation1.cpp"
#include"GetCrossover_self1.cpp"
#include"GetCrossover_global1.cpp"
#include"GetMutation.cpp"
#include"GetCrossover_self.cpp"
#include"GetCrossover_global.cpp"
bool cmp_bea(struct pop a, struct pop b)
{
	if (a.fit_value<b.fit_value)
		return true;
	else
		return false;
}
void work() {
	int eval, i, j, k, kk, index, flag;
	double threshold = 0.4;
	//	int pp=1;1

	double min_fitness;
	w_now = w_start;
	c1_now = c1_start;
	GenerateGraph();//��ʼ��ͼ
	srand(time(NULL));
	InitializePop();  //��ʼ����Ⱥ
	index = 1;//��Ⱥ���Ÿ���������ʼ��Ϊ1������
	min_fitness = pop[1].fit_value;
	eval = 1;
	clock_t start = clock();
	while (eval <= evaluations)
	{
		flag = 0;
		if (eval>1)
		{
			w_now = w_now - inerdec; //���¹���Ȩ��
			c1_now = c1_now - c1_dec;//���¼�������
		}
		//	c2_now=1-c1_now;
		if (eval == evaluations)//�������һ�ε�����ϵ��
		{
			w_now = 0.7;
			//			 c1_now=0.6;
			//		     c2_now=0.5;
		}
		for (i = 1; i <= popsize; i++) //����ÿ�����ӵ��ٶȺ�λ��
		{
			//			if (pop[i].fit_value<=fave)
			//				c1_now = 0.5*(1+(fave-pop[i].fit_value)/(fave-fmin));
			//c1_now = 0.5;
			//			else
			//     			c1_now = 0.5*(fmax-pop[i].fit_value)/(fmax-fave);
			// c1_now = 0.5;
			c2_now = 1 - c1_now;
			//			printf("c1= %lf c2= %lf\n",c1_now, c2_now);
			//           printf("%d evaluation %d particle mu:\n",eval,i); //��eval�ε�����i�����ӵı��죺
			if (eval<threshold*evaluations)
			{
				GetMutation(i); //����
								//			  printf("%d evaluation %d particle cs:\n",eval,i); //��eval�ε�����i�����ӵ����Ҹ�֪��
				GetCrossover_self(i); //���Ҹ�֪
									  //			  printf("%d evaluation %d particle cg:\n",eval,i); //��eval�ε�����i�����ӵ�ȫ�ָ�֪��
				GetCrossover_global(i); //ȫ�ָ�֪
			}
			else
			{
				if (eval == threshold*evaluations)
				{
					for (k = 1; k <= popsize; k++)
						for (kk = 1; kk <= (vertice - 1); kk++)
						{
							pop[k].edge[kk * 3 - 2] = gbest.edge[kk * 3 - 2];
							pop[k].edge[kk * 3 - 1] = gbest.edge[kk * 3 - 1];
						}
					/*                     for(k=1;k<=popsize;k++)
					{
					for(kk=1;kk<=(vertice-1);kk++)
					{
					pop[k].edge[kk*3-2]=gbest.edge[kk*3-2];
					pop[k].edge[kk*3-1]=gbest.edge[kk*3-1];
					printf("%d %d %d ",pop[k].edge[kk*3-2],pop[k].edge[kk*3-1],pop[k].edge[kk*3]);
					}
					printf("\n");
					}
					*/
				}
				GetMutation1(i); //����
								 //			  printf("%d evaluation %d particle cs:\n",eval,i); //��eval�ε�����i�����ӵ����Ҹ�֪��
				GetCrossover_self1(i); //���Ҹ�֪
									   //			  printf("%d evaluation %d particle cg:\n",eval,i); //��eval�ε�����i�����ӵ�ȫ�ָ�֪��
				GetCrossover_global1(i); //ȫ�ָ�֪
			}
			if (pbest[i].fit_value>pop[i].fit_value) //���¸����ӵ���ʷ�������Ž�
			{
				for (j = 1; j <= 3 * (vertice - 1); j++)
					pbest[i].edge[j] = pop[i].edge[j];
				pbest[i].fit_value = pop[i].fit_value;
			}
			if (pop[i].fit_value<min_fitness)//��¼��ǰ���Ž����������Ӧֵ
			{
				flag = 1;
				index = i;
				//				  pp=eval;
				min_fitness = pop[i].fit_value;
			}
		}
		if (flag)
		{
			for (j = 1; j <= 3 * (vertice - 1); j++)
				gbest.edge[j] = pop[index].edge[j];
			gbest.fit_value = min_fitness;
		}
		evalgbest[eval] = gbest.fit_value;
		//		printf("%d���������߳�Ϊ��%lf\n",eval,gbest.fit_value);
		eval++;
		//����Ӧѧϰ����
		fave = 0;
		ffmin = 10000000;
		ffmax = 0;
		for (i = 1; i <= popsize; i++)
		{
			fave = fave + pop[i].fit_value;
			if (pop[i].fit_value<ffmin)
				ffmin = pop[i].fit_value;
			if (pop[i].fit_value>ffmax)
				ffmax = pop[i].fit_value;
		}
		fave = fave / popsize;
	}

	clock_t finish = clock();
	printf("����ʱ��:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	printf("%d�����Ӿ���%d�ε������ҵ�����������Ϊ��\n", popsize, evaluations);
	for (j = 1; j <= 3 * (vertice - 1); j++)
		printf("%d ", gbest.edge[j]);
	printf("\n�������ӵ����߳�Ϊ��%lf\n", gbest.fit_value);
	FILE *fout;
	fout = fopen("result.txt", "w");
	for (j = 1; j <= 3 * (vertice - 1); j++)
		fprintf(fout, "%d ", gbest.edge[j]);
	//	fprintf(fout," %d %d",pp,index);
	fprintf(fout, "\n%lf", gbest.fit_value);
	fprintf(fout, "\n%d", evaluations);
	for (j = 1; j <= evaluations; j++)
		fprintf(fout, "\n%d %lf", j, evalgbest[j]);
	fclose(fout);
}
void work2() {
	int eval, index, flag;
	int i, j;
	int r1, r2;
	double r3;
	int r4;
	int r5;
	int r_bea;
	int temp;
	double min_fitness;
	GenerateGraph();//��ʼ��ͼ
	srand(time(NULL));
	InitializePop_GA();  //��ʼ����Ⱥ
	index = 1;//��Ⱥ���Ÿ���������ʼ��Ϊ1������
	min_fitness = pop[1].fit_value;
	eval = 1;
	pm = pm_start;
	cm = cm_start;
	clock_t start = clock();
	while (eval <= evaluations) {
		flag = 0;
		//crossover
		sort(pop + 1, pop + 1 + popsize, cmp_bea);
		for (i = popsize/2 + 1; i <= popsize; i++) {
			r_bea = (int)((rand() / (RAND_MAX + 1.0))*(popsize / 2)) + 1;
			if (eval < evaluations / 2) {
				GetCrossover_BEA(r_bea, i);
			}
			else {
				GetCrossover_BEA1(r_bea, i);
			}
		}
		//mutation
		for (i = 1; i <= popsize; i++) {
			if (eval < evaluations / 2) {
				GetMutation_GA(i);
			}
			else {
				GetMutation_GA1(i);
			}
		}
		//selection
		for (i = 1; i <= popsize; i++) {
			for (j = 1; j <= (vertice - 1) * 3; j++) {
				min_tree[j] = pop[i].edge[j];
			}
			pop[i].fit_value = Getfitness();
			if (pop[i].fit_value < min_fitness) {
				flag = 1;
				index = i;
				min_fitness = pop[i].fit_value;
			}
		}

		if (flag)
		{
			for (j = 1; j <= 3 * (vertice - 1); j++)
				gbest.edge[j] = pop[index].edge[j];
			gbest.fit_value = min_fitness;
		}
		evalgbest[eval] = gbest.fit_value;
		cm -= (cm_start - cm_end) / evaluations;
		pm -= (pm_start - pm_end) / evaluations;
		eval++;
	}
	clock_t finish = clock();
	printf("����ʱ��:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	printf("%d�����Ӿ���%d�ε������ҵ�����������Ϊ��\n", popsize, evaluations);
	for (j = 1; j <= 3 * (vertice - 1); j++)
		printf("%d ", gbest.edge[j]);
	printf("\n�������ӵ����߳�Ϊ��%lf\n", gbest.fit_value);
	FILE *fout;
	fout = fopen("result.txt", "w");
	for (j = 1; j <= 3 * (vertice - 1); j++)
		fprintf(fout, "%d ", gbest.edge[j]);
	//	fprintf(fout," %d %d",pp,index);
	fprintf(fout, "\n%lf", gbest.fit_value);
	fprintf(fout, "\n%d", evaluations);
	for (j = 1; j <= evaluations; j++)
		fprintf(fout, "\n%d %lf", j, evalgbest[j]);
	fclose(fout);
}
int main()
{
	work2();
	return 0;
}