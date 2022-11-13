int parent3[MAX];
void initial3(int n) {
	int i;
	for(i=1; i<=n; i++)
		parent3[i]=i;
}
int find_set3(int x) {
	int temp;
	if(parent3[x]==x) return x;
	else {
		temp=parent3[x];
		parent3[x]=find_set3(temp);
		return parent3[x];
	}
}
void union_set3(int a,int b) {
	int pa,pb;
	pa=find_set3(a);
	pb=find_set3(b);
	if(pa!=pb)
		parent3[pb]=pa;
}
struct tree3 {
	int s,e;
	int line_style;
} par3[1010],par3_best[1010],sur3[2020],new_res3[1010];
bool cmpp3(struct tree3 a,struct tree3 b) {
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_global_bydef(int cur) {
	double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur3;
	c=rand()/(RAND_MAX+1.0);
//	printf("%lf %lf\n",c,c1_now);

//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//	printf("当前粒子的适应度：%lf\n\n",pop[cur].fit_value);
//	printf("全局历史最优粒子的适应度：%lf\n\n",gbest.fit_value);

	if(c<c2_now) {
		for(i=1; i<=(vertice-1); i++) {
			par3[i].s=pop[cur].edge[i*3-2];
			par3[i].e=pop[cur].edge[i*3-1];
			par3[i].line_style=pop[cur].edge[i*3];
			if(par3[i].s>par3[i].e) {
				mid=par3[i].s;
				par3[i].s=par3[i].e;
				par3[i].e=mid;
				if(par3[i].line_style==0||par3[i].line_style==1)
					par3[i].line_style=!par3[i].line_style;
				else if(par3[i].line_style==2)
					par3[i].line_style=3;
				else if(par3[i].line_style==3)
					par3[i].line_style=2;
			}
		}


//   printf("par3粒子：\n");
//   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");

		for(i=1; i<=(vertice-1); i++) {
			par3_best[i].s=gbest.edge[i*3-2];
			par3_best[i].e=gbest.edge[i*3-1];
			par3_best[i].line_style=gbest.edge[i*3];
			if(par3_best[i].s>par3_best[i].e) {
				mid=par3_best[i].s;
				par3_best[i].s=par3_best[i].e;
				par3_best[i].e=mid;
				if(par3_best[i].line_style==0||par3_best[i].line_style==1)
					par3_best[i].line_style=!par3_best[i].line_style;
				else if(par3_best[i].line_style==2)
					par3_best[i].line_style=3;
				else if(par3_best[i].line_style==3)
					par3_best[i].line_style=2;
			}
		}
//	  printf("par3_best粒子：\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");



		sort(par3+1,par3+vertice,cmpp3);
		sort(par3_best+1,par3_best+vertice,cmpp3);

//	     printf("排序后par3粒子：\n");
//     for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par3_best粒子：\n");
// for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");

		initial3(vertice);
		for(i=1; i<=(vertice-1); i++) {
			sign1[i]=0;
			sign2[i]=0;
		}
		count_new=1;
		for(i=1; i<=(vertice-1); i++) {
			for(j=1; j<=(vertice-1); j++) {
				if(par3_best[j].s==par3[i].s)
					break;
			}
			for(; j<=(vertice-1); j++) {
				if(par3_best[j].s!=par3[i].s)
					break;
				if(par3_best[j].e==par3[i].e) {
					sign1[i]=1;
					sign2[j]=1;
//				union_set3(par3[i].s,par3[i].e);
					new_res3[count_new].s=par3_best[j].s;
					new_res3[count_new].e=par3_best[j].e;
					new_res3[count_new++].line_style=par3_best[j].line_style;
					break;
				}
			}
		}

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res3[i].s,new_res3[i].e,new_res3[i].line_style);
//	  printf("\nsign1:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

		count_sur3=1;
		for(i=1; i<=(vertice-1); i++) {
			if(!sign1[i]) {
//			  sur3[count_sur3].s=par3[i].s;
//			  sur3[count_sur3].e=par3[i].e;
//			  sur3[count_sur3++].line_style=par3[i].line_style;
				if(find_set3(par3[i].s)!=find_set3(par3[i].e)) {
					union_set3(par3[i].s,par3[i].e);
					sur3[count_sur3].s=par3[i].s;
					sur3[count_sur3].e=par3[i].e;
					sur3[count_sur3++].line_style=par3[i].line_style;
				}
			}
			if(!sign2[i]) {
//              sur3[count_sur3].s=par3_best[i].s;
//			  sur3[count_sur3].e=par3_best[i].e;
//			  sur3[count_sur3++].line_style=par3_best[i].line_style;
				if(find_set3(par3_best[i].s)!=find_set3(par3_best[i].e)) {
					union_set3(par3_best[i].s,par3_best[i].e);
					sur3[count_sur3].s=par3_best[i].s;
					sur3[count_sur3].e=par3_best[i].e;
					sur3[count_sur3++].line_style=par3_best[i].line_style;
				}
			}
		}

//	  printf("count_sur3:%d\n",count_sur3);
//	  for(i=1;i<count_sur3;i++)
//	    printf("%d %d %d\n",sur3[i].s,sur3[i].e,sur3[i].line_style);
//	  printf("\n");


		while(1) {
			if(count_sur3==vertice) break;
			i=(int)((rand()/(RAND_MAX+1.0))*(count_new-1))+1;
			if(find_set3(new_res3[i].s)!=find_set3(new_res3[i].e)) {
				sur3[count_sur3].s=new_res3[i].s;
				sur3[count_sur3].e=new_res3[i].e;
				sur3[count_sur3++].line_style=new_res3[i].line_style;
				union_set3(new_res3[i].s,new_res3[i].e);
			}
		}
		for(i=1; i<=(vertice-1); i++) {
			pop[cur].edge[i*3-2]=sur3[i].s;
			pop[cur].edge[i*3-1]=sur3[i].e;
			pop[cur].edge[i*3]=sur3[i].line_style;
		}

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

		for(i=1; i<=3*(vertice-1); i++)
			min_tree[i]=pop[cur].edge[i];
		pop[cur].fit_value=Getfitness();
	}
}
void GetCrossover_worst_bydef(int cur) {
	double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur3;
	c=rand()/(RAND_MAX+1.0);
//	printf("%lf %lf\n",c,c1_now);

//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//	printf("当前粒子的适应度：%lf\n\n",pop[cur].fit_value);
//	printf("全局历史最优粒子的适应度：%lf\n\n",gbest.fit_value);

	if(c<c2_now) {
		for(i=1; i<=(vertice-1); i++) {
			par3[i].s=pop[cur].edge[i*3-2];
			par3[i].e=pop[cur].edge[i*3-1];
			par3[i].line_style=pop[cur].edge[i*3];
			if(par3[i].s>par3[i].e) {
				mid=par3[i].s;
				par3[i].s=par3[i].e;
				par3[i].e=mid;
				if(par3[i].line_style==0||par3[i].line_style==1)
					par3[i].line_style=!par3[i].line_style;
				else if(par3[i].line_style==2)
					par3[i].line_style=3;
				else if(par3[i].line_style==3)
					par3[i].line_style=2;
			}
		}


//   printf("par3粒子：\n");
//   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");

		for(i=1; i<=(vertice-1); i++) {
			par3_best[i].s=gWorst.edge[i*3-2];
			par3_best[i].e=gWorst.edge[i*3-1];
			par3_best[i].line_style=gWorst.edge[i*3];
			if(par3_best[i].s>par3_best[i].e) {
				mid=par3_best[i].s;
				par3_best[i].s=par3_best[i].e;
				par3_best[i].e=mid;
				if(par3_best[i].line_style==0||par3_best[i].line_style==1)
					par3_best[i].line_style=!par3_best[i].line_style;
				else if(par3_best[i].line_style==2)
					par3_best[i].line_style=3;
				else if(par3_best[i].line_style==3)
					par3_best[i].line_style=2;
			}
		}
//	  printf("par3_best粒子：\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");



		sort(par3+1,par3+vertice,cmpp3);
		sort(par3_best+1,par3_best+vertice,cmpp3);

//	     printf("排序后par3粒子：\n");
//     for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par3_best粒子：\n");
// for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");

		initial3(vertice);
		for(i=1; i<=(vertice-1); i++) {
			sign1[i]=0;
			sign2[i]=0;
		}
		count_new=1;
		for(i=1; i<=(vertice-1); i++) {
			for(j=1; j<=(vertice-1); j++) {
				if(par3_best[j].s==par3[i].s)
					break;
			}
			for(; j<=(vertice-1); j++) {
				if(par3_best[j].s!=par3[i].s)
					break;
				if(par3_best[j].e==par3[i].e) {
					sign1[i]=1;
					sign2[j]=1;
//				union_set3(par3[i].s,par3[i].e);
					new_res3[count_new].s=par3_best[j].s;
					new_res3[count_new].e=par3_best[j].e;
					new_res3[count_new++].line_style=par3_best[j].line_style;
					break;
				}
			}
		}

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res3[i].s,new_res3[i].e,new_res3[i].line_style);
//	  printf("\nsign1:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

		count_sur3=1;
		for(i=1; i<=(vertice-1); i++) {
			if(!sign1[i]) {
//			  sur3[count_sur3].s=par3[i].s;
//			  sur3[count_sur3].e=par3[i].e;
//			  sur3[count_sur3++].line_style=par3[i].line_style;
				if(find_set3(par3[i].s)!=find_set3(par3[i].e)) {
					union_set3(par3[i].s,par3[i].e);
					sur3[count_sur3].s=par3[i].s;
					sur3[count_sur3].e=par3[i].e;
					sur3[count_sur3++].line_style=par3[i].line_style;
				}
			}
			if(!sign2[i]) {
//              sur3[count_sur3].s=par3_best[i].s;
//			  sur3[count_sur3].e=par3_best[i].e;
//			  sur3[count_sur3++].line_style=par3_best[i].line_style;
				if(find_set3(par3_best[i].s)!=find_set3(par3_best[i].e)) {
					union_set3(par3_best[i].s,par3_best[i].e);
					sur3[count_sur3].s=par3_best[i].s;
					sur3[count_sur3].e=par3_best[i].e;
					sur3[count_sur3++].line_style=par3_best[i].line_style;
				}
			}
		}

//	  printf("count_sur3:%d\n",count_sur3);
//	  for(i=1;i<count_sur3;i++)
//	    printf("%d %d %d\n",sur3[i].s,sur3[i].e,sur3[i].line_style);
//	  printf("\n");


		while(1) {
			if(count_sur3==vertice) break;
			i=(int)((rand()/(RAND_MAX+1.0))*(count_new-1))+1;
			if(find_set3(new_res3[i].s)!=find_set3(new_res3[i].e)) {
				sur3[count_sur3].s=new_res3[i].s;
				sur3[count_sur3].e=new_res3[i].e;
				sur3[count_sur3++].line_style=new_res3[i].line_style;
				union_set3(new_res3[i].s,new_res3[i].e);
			}
		}
		for(i=1; i<=(vertice-1); i++) {
			pop[cur].edge[i*3-2]=sur3[i].s;
			pop[cur].edge[i*3-1]=sur3[i].e;
			pop[cur].edge[i*3]=sur3[i].line_style;
		}

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

		for(i=1; i<=3*(vertice-1); i++)
			min_tree[i]=pop[cur].edge[i];
		pop[cur].fit_value=Getfitness();
	}
}
void GetCrossover_worstr_bydef(int cur) {
	double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur3;
	c=rand()/(RAND_MAX+1.0);
//	printf("%lf %lf\n",c,c1_now);

//	printf("当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");
//	printf("当前粒子的适应度：%lf\n\n",pop[cur].fit_value);
//	printf("全局历史最优粒子的适应度：%lf\n\n",gbest.fit_value);

	if(c<c2_now) {
		for(i=1; i<=(vertice-1); i++) {
			par3[i].s=randP.edge[i*3-2];
			par3[i].e=randP.edge[i*3-1];
			par3[i].line_style=randP.edge[i*3];
			if(par3[i].s>par3[i].e) {
				mid=par3[i].s;
				par3[i].s=par3[i].e;
				par3[i].e=mid;
				if(par3[i].line_style==0||par3[i].line_style==1)
					par3[i].line_style=!par3[i].line_style;
				else if(par3[i].line_style==2)
					par3[i].line_style=3;
				else if(par3[i].line_style==3)
					par3[i].line_style=2;
			}
		}


//   printf("par3粒子：\n");
//   for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");

		for(i=1; i<=(vertice-1); i++) {
			par3_best[i].s=gWorst.edge[i*3-2];
			par3_best[i].e=gWorst.edge[i*3-1];
			par3_best[i].line_style=gWorst.edge[i*3];
			if(par3_best[i].s>par3_best[i].e) {
				mid=par3_best[i].s;
				par3_best[i].s=par3_best[i].e;
				par3_best[i].e=mid;
				if(par3_best[i].line_style==0||par3_best[i].line_style==1)
					par3_best[i].line_style=!par3_best[i].line_style;
				else if(par3_best[i].line_style==2)
					par3_best[i].line_style=3;
				else if(par3_best[i].line_style==3)
					par3_best[i].line_style=2;
			}
		}
//	  printf("par3_best粒子：\n");
//for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");



		sort(par3+1,par3+vertice,cmpp3);
		sort(par3_best+1,par3_best+vertice,cmpp3);

//	     printf("排序后par3粒子：\n");
//     for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3[i].s,par3[i].e,par3[i].line_style);
//	  printf("\n");
//	  	  printf("排序后par3_best粒子：\n");
// for(i=1;i<=(vertice-1);i++)
//	    printf("%d %d %d\n",par3_best[i].s,par3_best[i].e,par3_best[i].line_style);
//	  printf("\n");

		initial3(vertice);
		for(i=1; i<=(vertice-1); i++) {
			sign1[i]=0;
			sign2[i]=0;
		}
		count_new=1;
		for(i=1; i<=(vertice-1); i++) {
			for(j=1; j<=(vertice-1); j++) {
				if(par3_best[j].s==par3[i].s)
					break;
			}
			for(; j<=(vertice-1); j++) {
				if(par3_best[j].s!=par3[i].s)
					break;
				if(par3_best[j].e==par3[i].e) {
					sign1[i]=1;
					sign2[j]=1;
//				union_set3(par3[i].s,par3[i].e);
					new_res3[count_new].s=par3_best[j].s;
					new_res3[count_new].e=par3_best[j].e;
					new_res3[count_new++].line_style=par3_best[j].line_style;
					break;
				}
			}
		}

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res3[i].s,new_res3[i].e,new_res3[i].line_style);
//	  printf("\nsign1:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
		//    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");

		count_sur3=1;
		for(i=1; i<=(vertice-1); i++) {
			if(!sign1[i]) {
//			  sur3[count_sur3].s=par3[i].s;
//			  sur3[count_sur3].e=par3[i].e;
//			  sur3[count_sur3++].line_style=par3[i].line_style;
				if(find_set3(par3[i].s)!=find_set3(par3[i].e)) {
					union_set3(par3[i].s,par3[i].e);
					sur3[count_sur3].s=par3[i].s;
					sur3[count_sur3].e=par3[i].e;
					sur3[count_sur3++].line_style=par3[i].line_style;
				}
			}
			if(!sign2[i]) {
//              sur3[count_sur3].s=par3_best[i].s;
//			  sur3[count_sur3].e=par3_best[i].e;
//			  sur3[count_sur3++].line_style=par3_best[i].line_style;
				if(find_set3(par3_best[i].s)!=find_set3(par3_best[i].e)) {
					union_set3(par3_best[i].s,par3_best[i].e);
					sur3[count_sur3].s=par3_best[i].s;
					sur3[count_sur3].e=par3_best[i].e;
					sur3[count_sur3++].line_style=par3_best[i].line_style;
				}
			}
		}

//	  printf("count_sur3:%d\n",count_sur3);
//	  for(i=1;i<count_sur3;i++)
//	    printf("%d %d %d\n",sur3[i].s,sur3[i].e,sur3[i].line_style);
//	  printf("\n");


		while(1) {
			if(count_sur3==vertice) break;
			i=(int)((rand()/(RAND_MAX+1.0))*(count_new-1))+1;
			if(find_set3(new_res3[i].s)!=find_set3(new_res3[i].e)) {
				sur3[count_sur3].s=new_res3[i].s;
				sur3[count_sur3].e=new_res3[i].e;
				sur3[count_sur3++].line_style=new_res3[i].line_style;
				union_set3(new_res3[i].s,new_res3[i].e);
			}
		}
		for(i=1; i<=(vertice-1); i++) {
			pop[cur].edge[i*3-2]=sur3[i].s;
			pop[cur].edge[i*3-1]=sur3[i].e;
			pop[cur].edge[i*3]=sur3[i].line_style;
		}

//	  	printf("新的当前粒子：\n");
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",pop[cur].edge[i]);
//	printf("\n");

		for(i=1; i<=3*(vertice-1); i++)
			min_tree[i]=pop[cur].edge[i];
		pop[cur].fit_value=Getfitness();
	}
}

