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
void work_pso() {
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
void work_abc() {
	int index, eval, flag;
	double min_fitness;
	double rij;
	int i, j;
	int k;
	int t;
	double para;
	double maxfit;
	double R_choose;
	int maxtrail;
	int R;
	int bestp;
	GenerateGraph();//��ʼ��ͼ
	srand(time(NULL));
	InitializePop_ABC();  //��ʼ����Ⱥ
	index = 1;//��Ⱥ���Ÿ���������ʼ��Ϊ1������
	min_fitness = pop[1].fit_value; 
	//printf("fitness=%lf\n", min_fitness);
	eval = 1;
	clock_t start = clock();
	while (eval <= evaluations) {
		//printf("eval=%d\n", eval);
		flag = 0;
		//sendemployedbees
		//printf("sendemployedbees\n");
		for (i = 1; i <= popsize; i++) {
			k = rand() % popsize;
			while (k == i) k = rand() % popsize;
			for (j = 1; j < vertice; j++) {
				rij = (rand() / double(RAND_MAX)) * 2 - 1;
				para = pop[i].edge[j * 3] + rij*(pop[i].edge[j * 3] - pop[k].edge[j * 3]);
				if (para <= 0) {
					employedbees[i].edge[j * 3] = 0;
					employedbees[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					employedbees[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else if (para <= 1 && para > 0) {
					employedbees[i].edge[j * 3] = 1;
					employedbees[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					employedbees[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else if (para <= 2 && para > 1) {
					employedbees[i].edge[j * 3] = 2;
					employedbees[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					employedbees[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else {
					employedbees[i].edge[j * 3] = 3;
					employedbees[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					employedbees[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
			}
			for (j = 1; j <= 3 * (vertice - 1); j++) {
				min_tree2[j] = employedbees[i].edge[j];
			}
			employedbees[i].fit_value = Getfitness2();
			//printf("employ fitness=%lf\n", employedbees[i].fit_value);
			if (employedbees[i].fit_value < pop[i].fit_value) {
				for (j = 1; j <= 3 * (vertice - 1); j++) {
					pop[i].edge[j] = employedbees[i].edge[j];
				}
				pop[i].fit_value = employedbees[i].fit_value;
				pop[i].trail = 0;
			}
			else {
				pop[i].trail++;
			}
		}
		//calculate
		//printf("calculate\n");
		maxfit = pop[1].fit_value;
		for (i = 2; i <= popsize; i++) {
			if (pop[i].fit_value > maxfit) {
				maxfit = pop[i].fit_value;
			}
		}
		for (i = 1; i <= popsize; i++) {
			pop[i].rfitness = (0.9*(pop[i].fit_value / maxfit)) + 0.1;
		}
		//sendonlookers
		//printf("sendonlookers\n");
		t = 0; i = 1;
		while (t < popsize) {
			//printf("t=%d\n", t);
			R_choose = rand() / double(RAND_MAX);
			if (R_choose < pop[i].rfitness) {
				t++;
				k = rand() % popsize;
				while (k == i) k = rand() % popsize;
				for (j = 1; j < vertice; j++) {
					rij = (rand() / double(RAND_MAX)) * 2 - 1;
					para = pop[i].edge[j * 3] + rij*(pop[i].edge[j * 3] - pop[k].edge[j * 3]);
					if (para <= 0) {
						onlooker[i].edge[j * 3] = 0;
						onlooker[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
						onlooker[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
					}
					else if (para <= 1 && para > 0) {
						onlooker[i].edge[j * 3] = 1;
						onlooker[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
						onlooker[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
					}
					else if (para <= 2 && para > 1) {
						onlooker[i].edge[j * 3] = 2;
						onlooker[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
						onlooker[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
					}
					else {
						onlooker[i].edge[j * 3] = 3;
						onlooker[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
						onlooker[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
					}
				}
				for (j = 1; j <= 3 * (vertice - 1); j++) {
					min_tree2[j] = onlooker[i].edge[j];
				}
				onlooker[i].fit_value = Getfitness2();
				//printf("onlooker fitness=%lf\n", onlooker[i].fit_value);
				if (onlooker[i].fit_value < pop[i].fit_value) {
					for (j = 1; j <= 3 * (vertice - 1); j++) {
						pop[i].edge[j] = onlooker[i].edge[j];
					}
					pop[i].fit_value = onlooker[i].fit_value;
					pop[i].trail = 0;
				}
				else {
					pop[i].trail++;
				}
			}
			i++;
			if (i == popsize + 1) {
				i = 1;
			}
		}
		//sendscoutbee
		//printf("sendscoutbee\n");
		maxtrail = 1;
		for (i = 2; i <= popsize; i++) {
			if (pop[i].trail > pop[maxtrail].trail) {
				maxtrail = i;
			}
		}
		if (pop[maxtrail].trail >= limit) {
			for (i = 1; i < vertice; i++) {
				R = rand() % 4;
				pop[maxtrail].edge[i * 3] = R;
				min_tree2[i * 3] = R;
				min_tree2[i * 3 - 1] = pop[maxtrail].edge[i * 3 - 1];
				min_tree2[i * 3 - 2] = pop[maxtrail].edge[i * 3 - 2];
			}
			pop[maxtrail].trail = 0;
			pop[maxtrail].fit_value = Getfitness2();
			//printf("scout fitness=%lf\n", pop[i].fit_value);
		}
		//select the best particle
		for (i = 1; i <= popsize; i++) {
			//printf("fitness=%lf\n", pop[i].fit_value);
			if (pop[i].fit_value<min_fitness)//��¼��ǰ���Ž����������Ӧֵ
			{
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
	work_abc();
	return 0;
}