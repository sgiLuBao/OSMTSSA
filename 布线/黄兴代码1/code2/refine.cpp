bool shar(struct str a,struct str b)
{
	return a.shared_value>b.shared_value;
}
void refine()
{
	int i,j,n1,n2,d1,d2;
	int pn,dg,pos;
	double t;
	for(i=1;i<=vertice;i++)
	{
		terminal[i].degree=0; 
		graph[i][2]=1; 
	}
	for(i=1;i<vertice;i++)
	{
	   edge[i].mark=true;
       n1=edge[i].s; 
	   n2=edge[i].e;
	   d1=terminal[n1].degree; 
	   d2=terminal[n2].degree;
	   terminal[n1].edge_pos[d1]=i;
       terminal[n1].degree++;
	   terminal[n2].edge_pos[d2]=i;
       terminal[n2].degree++;
	}
//	for(j=350;j<=355;j++){
//	printf("%d\n",terminal[j].degree);
//	for(i=0;i<terminal[j].degree;i++)
//		printf("%d ",edge[terminal[j].edge_pos[i]].index);
//	printf("\n");
//	}
//	FILE *f;
//    f=fopen("degree.txt","w"); 
//	for(i=1;i<=vertice;i++)
//	{
//		fprintf(f,"The %d-th point is %d degree:",terminal[i].num,terminal[i].degree);
//		for(j=0;j<terminal[i].degree;j++)
//       fprintf(f,"%d ",terminal[i].edge_pos[j]);
//		fprintf(f,"\n");
//	}
//    fclose(f);

	//   printf("顶点73度数：%d\n",terminal[73].degree);
//  printf("顶点73边所在位置：%d %d\n",terminal[73].edge_pos[0],terminal[73].edge_pos[1]);
//	printf("顶点73的边：%d %d %d %d\n",edge[terminal[73].edge_pos[0]].s,edge[terminal[73].edge_pos[0]].e,edge[terminal[73].edge_pos[1]].s,edge[terminal[73].edge_pos[1]].e);
//    printf("73:%.0lf %.0lf\n",graph[73][0],graph[73][1]);
//    printf("%d:%.0lf %.0lf\n",edge[terminal[73].edge_pos[0]].e,graph[edge[terminal[73].edge_pos[0]].e][0],graph[edge[terminal[73].edge_pos[0]].e][1]);
//	printf("%d:%.0lf %.0lf\n",edge[terminal[73].edge_pos[1]].s,graph[edge[terminal[73].edge_pos[1]].s][0],graph[edge[terminal[73].edge_pos[1]].s][1]);
//    int ind1,ind2;
//   ind1=edge[terminal[73].edge_pos[0]].index;
//	ind2=edge[terminal[73].edge_pos[1]].index;
//	printf("73 92:\n");
//	for(i=0;i<4;i++)
//	{
//		printf("方式%d:\n",i);
//		printf("hor:%.0lf %.0lf %.0lf\n",records2[ind1][i].posh,records2[ind1][i].sh,records2[ind1][i].eh);
 //       printf("45:%.0lf %.0lf %.0lf\n",records2[ind1][i].pos45,records2[ind1][i].s45,records2[ind1][i].e45);
//	    printf("135:%.0lf %.0lf %.0lf\n",records2[ind1][i].pos135,records2[ind1][i].s135,records2[ind1][i].e135);
//	}
//	printf("250 73:\n");
//	for(i=0;i<4;i++)
//	{
//		printf("方式%d:\n",i);
//		printf("hor:%.0lf %.0lf %.0lf\n",records2[ind2][i].posh,records2[ind2][i].sh,records2[ind2][i].eh);
//      printf("ver:%.0lf %.0lf %.0lf\n",records2[ind2][i].posv,records2[ind2][i].sv,records2[ind2][i].ev);
//       printf("45:%.0lf %.0lf %.0lf\n",records2[ind2][i].pos45,records2[ind2][i].s45,records2[ind2][i].e45);
//	    printf("135:%.0lf %.0lf %.0lf\n",records2[ind2][i].pos135,records2[ind2][i].s135,records2[ind2][i].e135);
//	}
//		count_length(); 
//	printf("%lf\n",final_len);
	
    for(i=1;i<=vertice;i++)
	  if(terminal[i].degree>1&&terminal[i].degree<5)
         optimal_substructure(i);
	  else 
	  {
	      opt_str[i].num=i;
		  opt_str[i].shared_value=-1;
	  }
    

//	printf("%d:%.0lf\n",opt_str[73].num,opt_str[73].shared_value);
//	printf("顶点%d的最优连接方式：%d %d\n",opt_str[73].num,opt_str[73].choice[0],opt_str[73].choice[1]);
    
	sort(opt_str+1,opt_str+1+vertice,shar);
//	for(i=1;i<=vertice;i++)
//		printf("顶点%d:%.0lf\n",opt_str[i].num,opt_str[i].shared_value);

	for(i=1;i<vertice;i++)
		edge_sign[i]=false;
	refine_sum=0;
	for(i=1;i<=vertice;i++)
	{
		if(refine_sum==vertice-1) break;
        pn=opt_str[i].num; 
		dg=terminal[pn].degree; 
        for(j=0;j<dg;j++)
		{
           pos=terminal[pn].edge_pos[j];
		   if(edge_sign[pos]==false) 
		   {
			   edge_sign[pos]=true; 
			   refine_sum++;
			   edge[pos].c=opt_str[i].choice[j];
		   }
		}
	}
//	if((ini_v_num==10&&barr_num==50)||(ini_v_num==10&&barr_num==43))
//	{	
//      dc=0;
//      for(i=ini_v_num+1;i<=vertice;i++)
//	  if(terminal[i].degree==2)
//		  judge_corner(i);
//	  t=1;
//	  for(i=1;i<=vertice;i++)
//	  {
//		if(graph[i][2]!=0){
//		   graph[i][2]=t;
//		   t=t+1;
//		}
//	  }
//	  int t1,t2;
//	  for(i=1;i<vertice;i++)
//	  {
//		if(edge[i].mark==true)
//		{
//		  t1=edge[i].s;t2=edge[i].e;
//		  edge[i].s=(int)graph[t1][2];
//		  edge[i].e=(int)graph[t2][2];
//		}
//	  }
//	  vertice-=dc;
//	}
    count_length();
}
