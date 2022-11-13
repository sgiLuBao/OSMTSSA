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

//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

	if(c<c1_now) {
		for(i=1; i<=(vertice-1); i++) { //i边
			par4[i].s=pop[cur].edge[i*3-2];
			par4[i].e=pop[cur].edge[i*3-1];
			par4[i].line_style=pop[cur].edge[i*3];
			if(par4[i].s>par4[i].e) { //这条边进行操作：编号小的点在前，编号大的点在后
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


		//    printf("par4粒子：\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4[i].s,par4[i].e,par4[i].line_style);
//	  printf("\n");

		for(i=1; i<=(vertice-1); i++) { //将当前粒子的历史最优解存入结构体中
			par4_best[i].s=pbest[cur].edge[i*3-2];
			par4_best[i].e=pbest[cur].edge[i*3-1];
			par4_best[i].line_style=pbest[cur].edge[i*3];
			if(par4_best[i].s>par4_best[i].e) { //如果起点编号大于终点编号，则交换位置
				mid=par4_best[i].s;
				par4_best[i].s=par4_best[i].e;
				par4_best[i].e=mid;
				if(par4_best[i].line_style==0||par4_best[i].line_style==1)//连接方式互换
					par4_best[i].line_style=!par4_best[i].line_style;
				else if(par4_best[i].line_style==2)
					par4_best[i].line_style=3;
				else if(par4_best[i].line_style==3)
					par4_best[i].line_style=2;
			}
		}
//	  printf("par4_best粒子：\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4_best[i].s,par4_best[i].e,par4_best[i].line_style);
//	  printf("\n");



		sort(par4+1,par4+vertice,cmpp4); //对粒子的边按照起点由小到大，终点由小到大的顺序排列
		sort(par4_best+1,par4_best+vertice,cmpp4);

		//     printf("排序后par4粒子：\n");
		//   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4[i].s,par4[i].e,par4[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par4_best粒子：\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par4_best[i].s,par4_best[i].e,par4_best[i].line_style);
//	  printf("\n");

		initial4(vertice);//并查集初始每点自己是自己的父亲
		for(i=1; i<=(vertice-1); i++) { //初始化标记数组，标记哪条边是共同边
			sign1[i]=0;
			sign2[i]=0;
		}
		count_new=1; //记录新粒子中当前的边数
		for(i=1; i<=(vertice-1); i++) { //寻找两个粒子中相同的边
			for(j=1; j<=(vertice-1); j++) { //找到个体历史最优粒子中与当前粒子第i条边起点相同的位置
				if(par4_best[j].s==par4[i].s) //找到跳出
					break;
			}
			for(; j<=(vertice-1); j++) { //个体历史最优粒子中寻找与当前粒子第i条边终点相同的边
				if(par4_best[j].s!=par4[i].s)  //起点不同，则不存在相同的边，跳出；
					break;
				if(par4_best[j].e==par4[i].e) { //找到相同的边
					sign1[i]=1; //当前粒子中该边标记为1
					sign2[j]=1; //个体历史最优粒子中该边标记位1
//				union_set4(par4[i].s,par4[i].e); //合并该边的两个端点为同一组
					new_res4[count_new].s=par4_best[j].s; //将共同边存入new_res4中
					new_res4[count_new].e=par4_best[j].e;
					new_res4[count_new++].line_style=par4_best[j].line_style;
					break;//跳出
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

		count_sur4=1; //记录挑完共同边后剩余的边数
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

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//
		for(i=1; i<=3*(vertice-1); i++)
			min_tree[i]=pop[cur].edge[i];
		pop[cur].fit_value=Getfitness();

//	  printf("适应度：%lf\n",pop[cur].fit_value);
	}
}
