struct node_s
{
	double pos,s,e;
}xa,ya;
struct obs
{
	int num; 
	double d; 
}ob[1000];
bool cc(struct obs a,struct obs b)
{
	return a.d<=b.d;
}
struct corner
{
	int num;
	int h;
	double d;
}ds[4];
bool cor(struct corner a,struct corner b)
{
	return a.d<b.d;
}
void corner_select()
{
   int i,j,k,t,sign1,pn;
   int p,q,s,x; 
   int min_p;
   int s_num,e_num,e_num1;
   int add_edge[2010][3],delete_edge[2010][4];
   double s_point[2010][2];
   double sx,sy,ex,ey;
   double x1,y1,x2,y2;
   double A,B,C;
   double xmin,xmax,ymin,ymax;
   s_num=0;e_num=0,e_num1=0;
   for(i=1;i<=(vertice-1);i++)
   {
	   p=edge[i].s;
	   q=edge[i].e;
	   s=edge[i].c;
	   x=edge[i].index;
	   if(!records1[x].c[s]) continue;
	   delete_edge[e_num1][0]=p;
	   delete_edge[e_num1][1]=q;
	   delete_edge[e_num1][2]=s;
	   delete_edge[e_num1++][3]=x;
       sx=graph[p][0];
	   sy=graph[p][1];
	   ex=graph[q][0];
	   ey=graph[q][1];
//	   if(times==0&&i==vertice-1)
//	   {
//		   printf("%d\n",records1[x].c[s]);
//         printf("%d %d\n",records1[x].serial_num[0][0],records1[x].serial_num[0][1]);
//	   }

	   for(j=0;j<records1[x].c[s];j++) 
	   {
		   ob[j].num=records1[x].serial_num[s][j];
		   if(sx<=barr[ob[j].num][0]&&sy>=barr[ob[j].num][1]&&sy<=barr[ob[j].num][3])
			   ob[j].d=barr[ob[j].num][0]-sx;
		   else if(sx<=barr[ob[j].num][0]&&sy>=barr[ob[j].num][3])
			   ob[j].d=(barr[ob[j].num][0]-sx)+(sy-barr[ob[j].num][3]);
		   else if(sx<=barr[ob[j].num][2]&&sx>=barr[ob[j].num][0]&&sy>=barr[ob[j].num][3])
			   ob[j].d=sy-barr[ob[j].num][3];
		   else if(sx>=barr[ob[j].num][2]&&sy>=barr[ob[j].num][3])
			   ob[j].d=(sx-barr[ob[j].num][2])+(sy-barr[ob[j].num][3]);
		   else if(sx>=barr[ob[j].num][2]&&sy>=barr[ob[j].num][1]&&sy<=barr[ob[j].num][3])
			   ob[j].d=sx-barr[ob[j].num][2];
		   else if(sx>=barr[ob[j].num][2]&&sy<=barr[ob[j].num][1])
			   ob[j].d=(sx-barr[ob[j].num][2])+(barr[ob[j].num][1]-sy);
           else if(sx>=barr[ob[j].num][0]&&sx<=barr[ob[j].num][2]&&sy<=barr[ob[j].num][1])
			   ob[j].d=barr[ob[j].num][1]-sy;
		   else
               ob[j].d=(barr[ob[j].num][0]-sx)+(barr[ob[j].num][1]-sy); 
	   }
	
	   sort(ob,ob+records1[x].c[s],cc);
//	   if(times==0&&i==vertice-1)
//	   printf("%d %d",ob[0].num,ob[1].num);
//	   printf("%d %d %d:\n",p,q,s);
//	   for(int ii=0;ii<records1[p][q].c[s];ii++)
//		   printf("%d ",ob[ii].num);
//	   printf("\n");
	   pn=p;

	   for(j=0;j<records1[x].c[s];j++)
	   {
          A=ey-sy;
		  B=sx-ex;
		  C=sy*ex-sx*ey;
		  ds[0].d=fabs(A*barr[ob[j].num][0]+B*barr[ob[j].num][1]+C);
          ds[1].d=fabs(A*barr[ob[j].num][0]+B*barr[ob[j].num][3]+C);
		  ds[2].d=fabs(A*barr[ob[j].num][2]+B*barr[ob[j].num][3]+C);
		  ds[3].d=fabs(A*barr[ob[j].num][2]+B*barr[ob[j].num][1]+C);
          ds[0].num=0;ds[1].num=1;ds[2].num=2;ds[3].num=3;
		  if(sx<=ex) 
		  {
			  xmin=sx;
			  xmax=ex;
		  }
		  else
		  {
			  xmin=ex;
			  xmax=sx;
		  }
		  if(sy<=ey)
		  {
			  ymin=sy;
			  ymax=ey;
		  }
		  else
		  {
			  ymin=ey;
			  ymax=sy;
		  }
		  if(barr[ob[j].num][0]>=xmin&&barr[ob[j].num][0]<=xmax&&barr[ob[j].num][1]>=ymin&&barr[ob[j].num][1]<=ymax)
			  ds[0].h=1;
		  else ds[0].h=0;
          if(barr[ob[j].num][0]>=xmin&&barr[ob[j].num][0]<=xmax&&barr[ob[j].num][3]>=ymin&&barr[ob[j].num][3]<=ymax)
			  ds[1].h=1;
		  else ds[1].h=0;
		  if(barr[ob[j].num][2]>=xmin&&barr[ob[j].num][2]<=xmax&&barr[ob[j].num][3]>=ymin&&barr[ob[j].num][3]<=ymax)
			  ds[2].h=1;
		  else ds[2].h=0;
		  if(barr[ob[j].num][2]>=xmin&&barr[ob[j].num][2]<=xmax&&barr[ob[j].num][1]>=ymin&&barr[ob[j].num][1]<=ymax)
			  ds[3].h=1;
		  else ds[3].h=0;
          sort(ds,ds+4,cor);
		  min_p=-1;
		  for(t=0;t<4;t++)
		  {
			  if(cor_sign[ob[j].num][ds[t].num]==false&&ds[t].h==1)
			  {
				  min_p=ds[t].num;
				  break;
			  }
		  }	 
		  if(min_p==-1) 
		  {
			  for(t=0;t<4;t++)
				  if(cor_sign[ob[j].num][ds[t].num]==false)
				  {
					  min_p=ds[t].num;
					  break;
				  }
		  }
		  if(min_p==-1) {min_p=ds[0].num;}
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
          x1=sx;y1=sy;x2=s_point[s_num][0];y2=s_point[s_num][1];
		  xa.pos=y2;ya.pos=x1;
		  if(x1>x2)
		  {
			  xa.s=x2;
			  xa.e=x1;
		  }
		  else
		  {
			  xa.s=x1;
			  xa.e=x2;
		  }
		  if(y1>y2)
		  {
			  ya.s=y2; 
			  ya.e=y1; 
		  }
		  else 
		  {
              ya.s=y1;
			  ya.e=y2;
		  }
		  sign1=0; 
		  for(k=1;k<=barr_num;k++)
		  {	          
			  if(!(xa.pos<=barr[k][1]||xa.pos>=barr[k][3]||xa.e<=barr[k][0]||xa.s>=barr[k][2]))
			  {  
				  sign1=1;
				  break;
			  }
              if(!(ya.pos<=barr[k][0]||ya.pos>=barr[k][2]||ya.e<=barr[k][1]||ya.s>=barr[k][3]))
			  {
				  sign1=1;
				  break;
			  }
		  }
		  add_edge[e_num][0]=pn;
		  add_edge[e_num][1]=vertice+s_num+1;
		  if(!sign1)       
			 add_edge[e_num++][2]=2;
		  else
		     add_edge[e_num++][2]=3;
		  pn=vertice+s_num+1;
		  sx=s_point[s_num][0];
		  sy=s_point[s_num][1];
		  s_num++;		  
	   }
	   x1=sx;y1=sy;x2=graph[q][0];y2=graph[q][1];
	   xa.pos=y2;ya.pos=x1;
		  if(x1>x2)
		  {
			  xa.s=x2;
			  xa.e=x1;
		  }
		  else
		  {
			  xa.s=x1;
			  xa.e=x2;
		  }
		  if(y1>y2)
		  {
			  ya.s=y2; 
			  ya.e=y1; 
		  }
		  else 
		  {
              ya.s=y1;
			  ya.e=y2;
		  }
		  sign1=0; 
		  for(k=1;k<=barr_num;k++)
		  {	          
			  if(!(xa.pos<=barr[k][1]||xa.pos>=barr[k][3]||xa.e<=barr[k][0]||xa.s>=barr[k][2]))
			  {  
				  sign1=1;
				  break;
			  }
              if(!(ya.pos<=barr[k][0]||ya.pos>=barr[k][2]||ya.e<=barr[k][1]||ya.s>=barr[k][3]))
			  {
				  sign1=1;
				  break;
			  }
		  }
		  add_edge[e_num][0]=pn;
		  add_edge[e_num][1]=q;
		  if(!sign1)       
			 add_edge[e_num++][2]=2;
		  else
		     add_edge[e_num++][2]=3;
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
		fprintf(f_out,"%d %d %d %d\n",delete_edge[i][0],delete_edge[i][1],delete_edge[i][2],delete_edge[i][3]);
	fclose(f_out);
}
