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
void work1() {
	int eval, i, j, k, kk, index, flag;
	double threshold = 0.4;
	//	int pp=1;1

	double min_fitness;
	w_now = w_start;
	c1_now = c1_start;
	GenerateGraph();//初始化图
	srand(time(NULL));
	InitializePop();  //初始化种群
	index = 1;//种群最优个体索引初始化为1号粒子
	min_fitness = pop[1].fit_value;
	eval = 1;
	clock_t start = clock();
	while (eval <= evaluations)
	{
		flag = 0;
		if (eval>1)
		{
			w_now = w_now - inerdec; //更新惯性权重
			c1_now = c1_now - c1_dec;//更新加速因子
		}
		//	c2_now=1-c1_now;
		if (eval == evaluations)//设置最后一次迭代的系数
		{
			w_now = 0.7;
			//			 c1_now=0.6;
			//		     c2_now=0.5;
		}
		for (i = 1; i <= popsize; i++) //更新每个粒子的速度和位置
		{
			//			if (pop[i].fit_value<=fave)
			//				c1_now = 0.5*(1+(fave-pop[i].fit_value)/(fave-fmin));
			//c1_now = 0.5;
			//			else
			//     			c1_now = 0.5*(fmax-pop[i].fit_value)/(fmax-fave);
			// c1_now = 0.5;
			c2_now = 1 - c1_now;
			//			printf("c1= %lf c2= %lf\n",c1_now, c2_now);
			//           printf("%d evaluation %d particle mu:\n",eval,i); //第eval次迭代第i个粒子的变异：
			if (eval<threshold*evaluations)
			{
				GetMutation(i); //变异
								//			  printf("%d evaluation %d particle cs:\n",eval,i); //第eval次迭代第i个粒子的自我感知：
				GetCrossover_self(i); //自我感知
									  //			  printf("%d evaluation %d particle cg:\n",eval,i); //第eval次迭代第i个粒子的全局感知：
				GetCrossover_global(i); //全局感知
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
				GetMutation1(i); //变异
								 //			  printf("%d evaluation %d particle cs:\n",eval,i); //第eval次迭代第i个粒子的自我感知：
				GetCrossover_self1(i); //自我感知
									   //			  printf("%d evaluation %d particle cg:\n",eval,i); //第eval次迭代第i个粒子的全局感知：
				GetCrossover_global1(i); //全局感知
			}
			if (pbest[i].fit_value>pop[i].fit_value) //更新该粒子的历史个体最优解
			{
				for (j = 1; j <= 3 * (vertice - 1); j++)
					pbest[i].edge[j] = pop[i].edge[j];
				pbest[i].fit_value = pop[i].fit_value;
			}
			if (pop[i].fit_value<min_fitness)//记录当前最优解的索引和适应值
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
		//		printf("%d代的最优线长为：%lf\n",eval,gbest.fit_value);
		eval++;
		//自适应学习因子
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
	printf("运行时间:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	printf("%d个粒子经过%d次迭代，找到的最优粒子为：\n", popsize, evaluations);
	for (j = 1; j <= 3 * (vertice - 1); j++)
		printf("%d ", gbest.edge[j]);
	printf("\n最优粒子的总线长为：%lf\n", gbest.fit_value);
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
	int index, eval, flag;
	int i, j;
	int r1, r2, r3;
	int r;
	double min_fitness;
	double para;
	double cr;
	GenerateGraph();//初始化图
	srand(time(NULL));
	InitializePop_DE();  //初始化种群
	index = 1;//种群最优个体索引初始化为1号粒子
	min_fitness = pop[1].fit_value;
	eval = 1;
	clock_t start = clock();
	while (eval <= evaluations)
	{
		flag = 0;
		for (i = 1; i <= popsize; i++) //更新每个粒子的速度和位置
		{
			//Mutation
			r1 = rand() % popsize;
			while (r1 == i) {
				r1 = rand() % popsize;
			}
			r2 = rand() % popsize;
			while (r2 == i || r2 == r1) {
				r2 = rand() % popsize;
			}
			r3 = rand() % popsize;
			while (r3 == i || r3 == r1 || r3 == r2) {
				r3 = rand() % popsize;
			}
			for (j = 1; j < vertice; j++) {
				para = pop[r1].edge[j * 3] + F*(pop[r2].edge[j * 3] - pop[r3].edge[j * 3]);
				if (para < 1) {
					pop2[i].edge[j * 3] = 0;
					pop2[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					pop2[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else if (para < 2 && para >= 1) {
					pop2[i].edge[j * 3] = 1;
					pop2[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					pop2[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else if (para < 3 && para >= 2) {
					pop2[i].edge[j * 3] = 2;
					pop2[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					pop2[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
				else {
					pop2[i].edge[j * 3] = 3;
					pop2[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					pop2[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
			}
			//Crossover
			for (j = 1; j < vertice; j++) {
				cr = rand() / double(RAND_MAX);
				if (cr < CR) {
					pop3[i].edge[j * 3] = pop2[i].edge[j * 3];
					pop3[i].edge[j * 3 - 1] = pop2[i].edge[j * 3 - 1];
					pop3[i].edge[j * 3 - 2] = pop2[i].edge[j * 3 - 2];
				}
				else {
					pop3[i].edge[j * 3] = pop[i].edge[j * 3];
					pop3[i].edge[j * 3 - 1] = pop[i].edge[j * 3 - 1];
					pop3[i].edge[j * 3 - 2] = pop[i].edge[j * 3 - 2];
				}
			}
			for (j = 1; j <= 3 * (vertice - 1); j++) {
				min_tree2[j] = pop3[i].edge[j];
			}
			pop3[i].fit_value = Getfitness2();
		}
		//Selection
		for (i = 1; i <= popsize; i++) {
			if (pop3[i].fit_value < pop[i].fit_value) {
				pop[i].fit_value = pop3[i].fit_value;
				for (j = 1; j <= 3 * (vertice - 1); j++) {
					pop[i].edge[j] = pop3[i].edge[j];
				}
				if (pop[i].fit_value<min_fitness)//记录当前最优解的索引和适应值
				{
					flag = 1;
					index = i;
					min_fitness = pop[i].fit_value;
				}
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
	printf("运行时间:%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
	printf("%d个粒子经过%d次迭代，找到的最优粒子为：\n", popsize, evaluations);
	for (j = 1; j <= 3 * (vertice - 1); j++)
		printf("%d ", gbest.edge[j]);
	printf("\n最优粒子的总线长为：%lf\n", gbest.fit_value);
	FILE *fout;
	fout = fopen("result.txt", "w");
	for (j = 1; j <= 3 * (vertice - 1); j++)
		fprintf(fout, "%d ", gbest.edge[j]);
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