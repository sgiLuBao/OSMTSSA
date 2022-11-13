struct node_s
{
	double pos,s,e;
}xa,ya;
struct obs
{
	int num; 
	double d; 
}ob[60];
bool ccc(struct obs a,struct obs b)
{
	return a.d<=b.d;
}
struct corrner
{
	int num;
	double d;
}dis[4];
bool corr(struct corrner a,struct corrner b)
{
	return a.d<b.d;
}
void adjusting()
{
   int i,j,t,pn;
   int p,q,s; 
   int min_p;
   int s_num,e_num,e_num1;
   double s_point[2010][2];
   int add_edge[2010][3],delete_edge[2010][3];
   double sx,sy,ex,ey;
   double center_x,center_y;
   double A,B,C;
   s_num=0;e_num=0,e_num1=0;
   for(i=1;i<=(vertice-1);i++)
   {
	   p=min_tree[i*3-2];
	   q=min_tree[i*3-1];
	   s=min_tree[i*3];
	   if(!records1[p][q].c[s]) continue;
//	   printf("%d %d %d %d\n",p,q,s,records1[p][q].c[s]);
	   delete_edge[e_num1][0]=p;
	   delete_edge[e_num1][1]=q;
	   delete_edge[e_num1++][2]=s;
       sx=graph[p][0];
	   sy=graph[p][1];
	   ex=graph[q][0];
	   ey=graph[q][1];
	   for(j=0;j<records1[p][q].c[s];j++) 
	   {
		   ob[j].num=records1[p][q].serial_num[s][j];
		   center_x=(barr[records1[p][q].serial_num[s][j]][0]+barr[records1[p][q].serial_num[s][j]][2])/2;
		   center_y=(barr[records1[p][q].serial_num[s][j]][1]+barr[records1[p][q].serial_num[s][j]][3])/2;
	       ob[j].d=(sx-center_x)*(sx-center_x)+(sy-center_y)*(sy-center_y);
	   }
	   sort(ob,ob+records1[p][q].c[s],ccc);
//	   printf("%d %d %d:\n",p,q,s);
//	   for(int ii=0;ii<records1[p][q].c[s];ii++)
//		   printf("%d ",ob[ii].num);
//	   printf("\n");
	   pn=p;
	   for(j=0;j<records1[p][q].c[s];j++)
	   {
          A=ey-sy;
		  B=sx-ex;
		  C=sy*ex-sx*ey;
		  dis[0].d=fabs(A*barr[ob[j].num][0]+B*barr[ob[j].num][1]+C)/(A*A+B*B);
          dis[1].d=fabs(A*barr[ob[j].num][0]+B*barr[ob[j].num][3]+C)/(A*A+B*B);
		  dis[2].d=fabs(A*barr[ob[j].num][2]+B*barr[ob[j].num][3]+C)/(A*A+B*B);
		  dis[3].d=fabs(A*barr[ob[j].num][2]+B*barr[ob[j].num][1]+C)/(A*A+B*B);
          dis[0].num=0;dis[1].num=1;dis[2].num=2;dis[3].num=3;
          sort(dis,dis+4,corr);
		  for(t=0;t<4;t++)
		  {
			  if(cor_sign[ob[j].num][dis[t].num]==false)
			  {
				  min_p=dis[t].num;
				  break;
			  }
		  }
		  cor_sign[ob[j].num][min_p]=true;
		  if(min_p==0)
		  {
			  s_point[s_num][0]=barr[ob[j].num][0];
			  s_point[s_num][1]=barr[ob[j].num][1];
		  }
		  else if(min_p==1)
		  {
			  s_point[s_num][0]=barr[ob[j].num][0];
			  s_point[s_num][1]=barr[ob[j].num][3];
		  }
		  else if(min_p==2)
		  {
			  s_point[s_num][0]=barr[ob[j].num][2];
			  s_point[s_num][1]=barr[ob[j].num][3];
		  }
		  else
		  {
              s_point[s_num][0]=barr[ob[j].num][2];
			  s_point[s_num][1]=barr[ob[j].num][1];
		  }
          add_edge[e_num][0]=pn;
		  add_edge[e_num][1]=vertice+s_num+1;      
		  add_edge[e_num++][2]=2;
		  pn=vertice+s_num+1;
		  sx=s_point[s_num][0];
		  sy=s_point[s_num][1];
		  s_num++;
	   }
	   add_edge[e_num][0]=pn;
	   add_edge[e_num][1]=q;
	   add_edge[e_num++][2]=2;
   }
   FILE *f_out;
// printf("%d\n",s_num);
// for(i=0;i<s_num;i++)
//	   printf("%lf %lf\n",s_point[i][0],s_point[i][1]);
    f_out=fopen("steiner.txt","w");
	fprintf(f_out,"%d\n",s_num);
	for(i=0;i<s_num;i++)
		fprintf(f_out,"%.0lf %.0lf\n",s_point[i][0],s_point[i][1]);
    fclose(f_out);
	f_out=fopen("add.txt","w");
    fprintf(f_out,"%d\n",e_num);
    for(i=0;i<e_num;i++)
	  fprintf(f_out,"%d %d %d\n",add_edge[i][0],add_edge[i][1],add_edge[i][2]);
	fclose(f_out);
	f_out=fopen("delete.txt","w");
    fprintf(f_out,"%d\n",e_num1);
    for(i=0;i<e_num1;i++)
		fprintf(f_out,"%d %d %d\n",delete_edge[i][0],delete_edge[i][1],delete_edge[i][2]);
	fclose(f_out);
}