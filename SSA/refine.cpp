#define D 4
void refine()
{
    int i,k,f1,f2,f3,f4,a,b,c,d,t1,t2,t3;
	double mid_fit;
    for(k=1;k<=vertice;k++) 
		pin[k].sum=0;	
	for(k=1;k<=(vertice-1);k++)
	{
		 min_tree[k*3-2]=gbest.edge[k*3-2];
		 min_tree[k*3-1]=gbest.edge[k*3-1];
		 min_tree[k*3]=gbest.edge[k*3];
		 if(pin[min_tree[k*3-2]].sum<D) 
		 {
			 pin[min_tree[k*3-2]].sum++; 
			 pin[min_tree[k*3-2]].code_pos[pin[min_tree[k*3-2]].sum]=k*3;
		     pin[min_tree[k*3-2]].p_pos[pin[min_tree[k*3-2]].sum]= min_tree[k*3-1];
		 }
		 if(pin[min_tree[k*3-1]].sum<D) 
		 {
			 pin[min_tree[k*3-1]].sum++;
			 pin[min_tree[k*3-1]].code_pos[pin[min_tree[k*3-1]].sum]=k*3;
		     pin[min_tree[k*3-1]].p_pos[pin[min_tree[k*3-1]].sum]= min_tree[k*3-2];
		 }
	}

//	for(k=1;k<=3*(vertice-1);k++)
 //    printf("%d ",min_tree[k]);
//	printf("\n");

//for(i=1;i<=vertice;i++)
//	{
//		printf("The %dth:%d\n",i,pin[i].sum);
//	    for(j=1;j<=pin[i].sum;j++)
//			printf("%d ",pin[i].p_pos[j]);
//		printf("\n");
//	}


	for(i=1;i<=vertice;i++)
	{
       if(pin[i].sum==1) 
	   {
//		   continue;
		   for(a=0;a<=3;a++) 
		   {
			   if(records1[i][pin[i].p_pos[1]].c[a]!=0) 
			   {
//				   printf("%d %d %d\n",i,pin[i].p_pos[1],a);
				   continue;
			   }
			   f1=min_tree[pin[i].code_pos[1]];
			   min_tree[pin[i].code_pos[1]]=a;
			   mid_fit=Getfitness(); 
		       if((gbest.fit_value-mid_fit)>1e-7) 
			   {
			      gbest.edge[pin[i].code_pos[1]]=a;
			      gbest.fit_value=mid_fit;
			   }
		       else  min_tree[pin[i].code_pos[1]]=f1;
		   }
	   }
	   if(pin[i].sum==2) 
	   {
//		   continue;
		   for(a=0;a<=3;a++)
		   {
			   if(records1[i][pin[i].p_pos[1]].c[a]!=0)
			   {
				   continue;
			   }
			   f1=min_tree[pin[i].code_pos[1]];
			   min_tree[pin[i].code_pos[1]]=a;
		       t1=0;
			   for(b=0;b<=3;b++)
			   {
                  if(records1[i][pin[i].p_pos[2]].c[b]!=0)
				  {
					  continue;
				  }
				  f2=min_tree[pin[i].code_pos[2]];
			      min_tree[pin[i].code_pos[2]]=b;
                  mid_fit=Getfitness();
		          if((gbest.fit_value-mid_fit)>1e-7)
				  {
					gbest.edge[pin[i].code_pos[1]]=a;
					gbest.edge[pin[i].code_pos[2]]=b;
			        gbest.fit_value=mid_fit;
					t1=1;
				  }
		          else  
					 min_tree[pin[i].code_pos[2]]=f2; 
			   }
			   if(!t1) min_tree[pin[i].code_pos[1]]=f1;
		   }
	   }
	   if(pin[i].sum==3)
	   {
//		   continue;
		   for(a=0;a<=3;a++)
		   {
			   if(records1[i][pin[i].p_pos[1]].c[a]!=0) continue;
			   f1=min_tree[pin[i].code_pos[1]];
			   min_tree[pin[i].code_pos[1]]=a;
			   t1=0;
			   for(b=0;b<=3;b++)
			   {
				   if(records1[i][pin[i].p_pos[2]].c[b]!=0) continue;
				   f2=min_tree[pin[i].code_pos[2]];
			       min_tree[pin[i].code_pos[2]]=b;
			       t2=0;
				   for(c=0;c<=3;c++)
				   {
                       if(records1[i][pin[i].p_pos[3]].c[c]!=0) continue;
					   f3=min_tree[pin[i].code_pos[3]];
			           min_tree[pin[i].code_pos[3]]=c;
                       mid_fit=Getfitness(); 
		               if((gbest.fit_value-mid_fit)>1e-7) 
					   {
			             gbest.edge[pin[i].code_pos[1]]=a;
					     gbest.edge[pin[i].code_pos[2]]=b;
						 gbest.edge[pin[i].code_pos[3]]=c;
			             gbest.fit_value=mid_fit;
					     t1=1;t2=1;
					   }
		               else  
					   min_tree[pin[i].code_pos[3]]=f3; 
				   }
				   if(!t2) min_tree[pin[i].code_pos[2]]=f2;
			   }
			   if(!t1) min_tree[pin[i].code_pos[1]]=f1;
		   }
	   }
	   if(pin[i].sum==4)
	   {
//		   continue;
		   for(a=0;a<=3;a++)
		   {
			   if(records1[i][pin[i].p_pos[1]].c[a]!=0) continue;
			   f1=min_tree[pin[i].code_pos[1]];
			   min_tree[pin[i].code_pos[1]]=a;
			   t1=0;
			   for(b=0;b<=3;b++)
			   {
				   if(records1[i][pin[i].p_pos[2]].c[b]!=0) continue;
				   f2=min_tree[pin[i].code_pos[2]];
			       min_tree[pin[i].code_pos[2]]=b;
			       t2=0;
				   for(c=0;c<=3;c++)
				   {
                     if(records1[i][pin[i].p_pos[3]].c[c]!=0) continue;
					   f3=min_tree[pin[i].code_pos[3]];
			           min_tree[pin[i].code_pos[3]]=c;
			           t3=0;
					   for(d=0;d<=3;d++)
					   {
					     if(records1[i][pin[i].p_pos[4]].c[d]!=0) continue;
						 f4=min_tree[pin[i].code_pos[4]];
			             min_tree[pin[i].code_pos[4]]=d;
                         mid_fit=Getfitness(); 
		                 if((gbest.fit_value-mid_fit)>1e-7) 
						 {
			               gbest.edge[pin[i].code_pos[1]]=a;
					       gbest.edge[pin[i].code_pos[2]]=b;
						   gbest.edge[pin[i].code_pos[3]]=c;
						   gbest.edge[pin[i].code_pos[4]]=d;
			               gbest.fit_value=mid_fit;
					       t1=1;t2=1;t3=1;
						 }
						 else  
					       min_tree[pin[i].code_pos[4]]=f4; 
					   }
					   if(!t3) min_tree[pin[i].code_pos[3]]=f3;
				   }
				   if(!t2) min_tree[pin[i].code_pos[2]]=f2;
			   }
			   if(!t1) min_tree[pin[i].code_pos[1]]=f1;
		   }
	   }
	}
//    for(i=1;i<=3*(vertice-1);i++)
//	    printf("%d ",gbest.edge[i]);
//	printf("\n%lf\n",gbest.fit_value);
//	FILE *fout;
//	fout=fopen("jieguo.txt","w");
//	for(j=1;j<=3*(vertice-1);j++)
//		fprintf(fout,"%d ",gbest.edge[j]);
//	fprintf(fout," %d %d",pp,index);
//	fprintf(fout,"\n%lf",gbest.fit_value);
//	fclose(fout);
}
