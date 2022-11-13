struct node3
{
	double pos,s,e;
}x,y;
struct node4
{
	double sx,sy,ex,ey;
}x_45,x_135;
void pre_treatment()
{
    int i,j,k,sp,m,flag,cc,ii;
	double x1,x2,y1,y2,fx,fy,midx,midy,p,q,crop,cro_point[2][2];
	double l,r,t,b;
	for(i=1;i<=vertice;i++)
	{
		for(j=1;j<=vertice;j++)
	   {
			for(k=0;k<4;k++)
               records1[i][j].c[k]=0;
		}
	}
	for(i=1;i<=vertice-1;i++)
	{
       for(j=i+1;j<=vertice;j++)
	   {
		   for(sp=0;sp<=3;sp++)
		   {
	//	      if(i==1&&j==2&&sp==1) printf("%lf %lf %lf %lf %lf %lf\n",fx,fy,x1,y1,x2,y2);
			  x1=graph[i][0];
		      y1=graph[i][1];
		      x2=graph[j][0];
		      y2=graph[j][1];
		      fx=fabs(x1-x2);
		      fy=fabs(y1-y2);
			  m=sp;
			  x.pos=-1;x.s=-1;x.e=-1;
              y.pos=-1;y.s=-1;y.e=-1;
			  x_45.sx=999999999;x_45.sy=999999999;x_45.ex=999999999;x_45.ey=999999999;
              x_135.sx=999999999;x_135.sy=999999999;x_135.ex=999999999;x_135.ey=999999999;
			 if(x1<x2) 
			  {
				  l=x1;
				  r=x2;
			  }
			  else
			  {
				  l=x2;
				  r=x1;
			  }
			  if(y1<y2)
			  {
				  b=y1;
				  t=y2;
			  }
			  else
			  {
				  b=y2;
				  t=y1;
			  }

		  if(m==0||m==1)
			  {
                  if(fx==0||fy==0) 
				  { 
			         if(m==0)
					 {
                        x.pos=y1; 
				        y.pos=x1;
					 }
			         else
					 {
				        x.pos=y2;
				        y.pos=x2;
					 }
			   	     if(x1>x2)
					 {
				        x.s=x2; 
				        x.e=x1; 
					 }
			         else
					 {
                       x.s=x1;
				       x.e=x2;
					 }
			        if(y1>y2)
					{
				       y.s=y2; 
				       y.e=y1; 
					}
			        else 
					{
                       y.s=y1;
			  	       y.e=y2;
					}
				  }
		          else 
				  {
					 if(x1>x2) 
					 {
					   midx=x1;
					   midy=y1;
					   x1=x2;
					   y1=y2;
					   x2=midx;
                       y2=midy;
					   if(sp==0) m=1;
					   else m=0;
					 }

                     if(fx>fy) 
					 {
				       if(m==0) 
					   {
					      x.pos=y1;
				 	      x.s=x1;
					      x.e=x2-fy;
					      if(y1<y2) 
						  { 
						    x_45.sx=x2-fy;
						    x_45.sy=y1;
						    x_45.ex=x2;
						    x_45.ey=y2;
						  }
					      else 
						  {
                            x_135.sx=x2-fy;
						    x_135.sy=y1;
						    x_135.ex=x2;
						    x_135.ey=y2;
						  }
					   }
				       else 
					   {
					     x.pos=y2;
					     x.s=x1+fy;
					     x.e=x2;
					     if(y1<y2)
						 {
                      	   x_45.sx=x1;
						   x_45.sy=y1;
						   x_45.ex=x1+fy;
						   x_45.ey=y2;
						 }
					     else
						 {
                           x_135.sx=x1;
						   x_135.sy=y1;
						   x_135.ex=x1+fy;
						   x_135.ey=y2;
						 }
					   }
					 }
				     else 
					 {
                         if(m==0) 
						 {
					       y.pos=x1;
					       if(y1<y2)
						   {
					     	 x_45.sx=x1;
						     x_45.sy=y2-fx;
						     x_45.ex=x2;
						     x_45.ey=y2;
						     y.s=y1;
					         y.e=y2-fx;
						   }
					       else
						   { 
                             x_135.sx=x1;
						     x_135.sy=y2+fx;
						     x_135.ex=x2;
					      	 x_135.ey=y2;
					 	     y.s=y2+fx;
					         y.e=y1;
						   }
						 }
				         else
						 {
					         y.pos=x2;
					         if(y1<y2)
							 {
                             	x_45.sx=x1;
					          	x_45.sy=y1;
					        	x_45.ex=x2;
					          	x_45.ey=y1+fx;
					        	y.s=y1+fx;
				   	            y.e=y2;
							 }
					         else
							 {
                                x_135.sx=x1;
						        x_135.sy=y1;
						        x_135.ex=x2;
						        x_135.ey=y1-fx;
						        y.s=y2;
					            y.e=y1-fx;
							 }
						 }
					 }
				  } 
			  }
			  if(m==2||m==3)  
			  {
			       if(m==2)
				   {
				      x.pos=y2; 
				      y.pos=x1; 
				   }
			       else 
				   {
			          x.pos=y1;
				      y.pos=x2;
				   }
			       if(x1>x2)
				   {
				      x.s=x2; 
				      x.e=x1; 
				   }
		           else
				   {
                      x.s=x1;
				      x.e=x2;
				   }
			       if(y1>y2)
				   {
				      y.s=y2; 
				      y.e=y1; 
				   }
			       else 
				   {
                      y.s=y1;
				      y.e=y2;
				   }
			  }
			  
//			  if(sp==0&&i==3&&j==72) {
//				  printf("%lf %lf\n%lf %lf\n",x1,y1,x2,y2);
//				  printf("%d\n",m);
//				  printf("x:%lf %lf %lf\n y:%lf %lf %lf\n",x.pos,x.s,x.e,y.pos,y.s,y.e);
//			     printf("45:%lf %lf %lf %lf\n135:%lf %lf %lf %lf\n",x_45.sx,x_45.sy,x_45.ex,x_45.ey,x_135.sx,x_135.sy,x_135.ex,x_135.ey);
//			  }
     	      for(k=1;k<=barr_num;k++)
			  {	             
				if(barr[k][0]>=r||barr[k][1]>=t||barr[k][2]<=l||barr[k][3]<=b) continue;

			    if(x.pos!=-1&&x.e!=-1&&x.s!=-1&&!(x.pos<=barr[k][1]||x.pos>=barr[k][3]||x.e<=barr[k][0]||x.s>=barr[k][2]))//如果水平线完全在矩形之下或之上或之左或之右，则不相交
				{
                   records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;				  
				   records1[i][j].c[sp]++;
				   continue;
				}

			    if(y.e!=-1&&y.pos!=-1&&y.s!=-1&&!(y.pos<=barr[k][0]||y.pos>=barr[k][2]||y.e<=barr[k][1]||y.s>=barr[k][3]))//如果垂直线完全在矩形之左或之右或之下或之上，则不相交
				{
				   records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				   records1[i][j].c[sp]++;
				   continue;
				}
			    
			    if(x_45.sx!=999999999&&x_45.sy!=999999999&&x_45.ex!=999999999&&x_45.ey!=999999999)
				{
                   if((x_45.sx>barr[k][0]&&x_45.sx<barr[k][2]&&x_45.sy>barr[k][1]&&x_45.sy<barr[k][3])||(x_45.ex>barr[k][0]&&x_45.ex<barr[k][2]&&x_45.ey>barr[k][1]&&x_45.ey<barr[k][3]))//如果45度斜边有一个顶点在矩形内，则肯定相交
				   {
					  records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				      records1[i][j].c[sp]++;
				      continue; 				       
				   }
				   else
				   {
			         flag=0; 
			         cc=0;  
			         p=(x_45.ey-x_45.sy)/(x_45.ex-x_45.sx); 
			         q=x_45.sy-p*x_45.sx;
	                 
                     crop=(barr[k][1]-q)/p;
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=x_45.sx&&crop<=x_45.ex) 
					 { 
			     	    flag++; 
				        if(cc<2)
						{ 
				           cro_point[cc][0]=crop;
				           cro_point[cc++][1]=barr[k][1];
						}
					 }
			         crop=(barr[k][3]-q)/p;
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=x_45.sx&&crop<=x_45.ex) 
					 { 
			    	    flag++;
			            if(cc<2)
						{
			               cro_point[cc][0]=crop;
			               cro_point[cc++][1]=barr[k][3];
						}
					 }
		             crop=p*barr[k][0]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=x_45.sy&&crop<=x_45.ey)
					 {
				       flag++;
				       if(cc<2)
					   {
				         cro_point[cc][0]=barr[k][0];
				         cro_point[cc++][1]=crop;
					   }
					 }
			         crop=p*barr[k][2]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=x_45.sy&&crop<=x_45.ey)
					 {
				       flag++;
				       if(cc<2)
					   {
					     cro_point[cc][0]=barr[k][2];
				         cro_point[cc++][1]=crop;
					   }
					 }
			         if(flag==3||flag==4)
					 {
					  records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				      records1[i][j].c[sp]++;
				      continue; 
					 }
			         
					 if(flag==2)
					 { 
                        if(!(cro_point[0][0]==cro_point[1][0]&&cro_point[0][1]==cro_point[1][1]))
						{
						   records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				           records1[i][j].c[sp]++;
				           continue; 
						}
					 }
				   }
				}
				if(x_135.ex!=999999999&&x_135.ey!=999999999&&x_135.sx!=999999999&&x_135.sy!=999999999)
				{
                   if((x_135.sx>barr[k][0]&&x_135.sx<barr[k][2]&&x_135.sy>barr[k][1]&&x_135.sy<barr[k][3])||(x_135.ex>barr[k][0]&&x_135.ex<barr[k][2]&&x_135.ey>barr[k][1]&&x_135.ey<barr[k][3])) //如果135度斜边有一个顶点在矩形内，则肯定相交
				   {
					  records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				      records1[i][j].c[sp]++;
				      continue; 		       
				   }
			       else
				   {
			         flag=0;
			         cc=0;  
			         p=(x_135.ey-x_135.sy)/(x_135.ex-x_135.sx); 
			         q=x_135.sy-p*x_135.sx;
		             
                     crop=(barr[k][1]-q)/p; 
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=x_135.sx&&crop<=x_135.ex) 
					 { 
			           flag++; 
			           if(cc<2)
					   {
			            cro_point[cc][0]=crop;
				        cro_point[cc++][1]=barr[k][1];
					   }
					 }
			         crop=(barr[k][3]-q)/p;
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=x_135.sx&&crop<=x_135.ex) 
					 {
				        flag++;
				        if(cc<2)
						{
				         cro_point[cc][0]=crop;
			             cro_point[cc++][1]=barr[k][3];
						}
					 }
		             crop=p*barr[k][0]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=x_135.ey&&crop<=x_135.sy)
					 { 
				        flag++;
				        if(cc<2)
						{
			               cro_point[cc][0]=barr[k][0];
				           cro_point[cc++][1]=crop;
						}
					 }
			        crop=p*barr[k][2]+q;
			        if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=x_135.ey&&crop<=x_135.sy)
					{
				        flag++;
				        if(cc<2)
						{
				            cro_point[cc][0]=barr[k][2];
				            cro_point[cc++][1]=crop;
						}
					}
		      	    if(flag==3||flag==4)
					{
					  records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				      records1[i][j].c[sp]++;
				      continue; 
					}
			        if(flag==2)
					{ 
                      if(!(cro_point[0][0]==cro_point[1][0]&&cro_point[0][1]==cro_point[1][1])) 
					  { 
						 records1[i][j].serial_num[sp][records1[i][j].c[sp]]=k;
				         records1[i][j].c[sp]++;
				         continue; 
					  }
					}
				   }
				}
			 }
			 if(sp==0)
			 {
               records1[j][i].c[1]=records1[i][j].c[sp];
			   for(ii=0;ii<records1[i][j].c[sp];ii++)
                records1[j][i].serial_num[1][ii]=records1[i][j].serial_num[sp][ii];
			 }
             else if(sp==1)
			 {
               records1[j][i].c[0]=records1[i][j].c[sp];
			   for(ii=0;ii<records1[i][j].c[sp];ii++)
                records1[j][i].serial_num[0][ii]=records1[i][j].serial_num[sp][ii];
			 }
			 else if(sp==2)
			 {
               records1[j][i].c[3]=records1[i][j].c[sp];
			   for(ii=0;ii<records1[i][j].c[sp];ii++)
                records1[j][i].serial_num[3][ii]=records1[i][j].serial_num[sp][ii];
			 }
             else 
			 {
               records1[j][i].c[2]=records1[i][j].c[sp];
			   for(ii=0;ii<records1[i][j].c[sp];ii++)
                records1[j][i].serial_num[2][ii]=records1[i][j].serial_num[sp][ii];
			 }
      }	 	   
   }
 }
 for(i=1;i<=vertice;i++)
 {
	 for(j=1;j<=vertice;j++)
	     for(sp=0;sp<4;sp++)
	     if(records1[i][j].c[sp]>100)
		 printf("%d %d: %d \n",i,j,records1[i][j].c[sp]);
 }

//	    printf("1 7: %d %d %d %d\n",records1[1][7].c[0],records1[1][7].c[1],records1[1][7].c[2],records1[1][7].c[3]);
//		for(i=0;i<4;i++)
//		{
//			printf("1 7 %d:",i);
//			for(j=0;j<records1[1][7].c[i];j++)
//				printf("%d ",records1[1][7].serial_num[i][j]);
//			printf("\n");		
//		}
//		printf("\n");
//		printf("7 1: %d %d %d %d\n",records1[7][1].c[0],records1[7][1].c[1],records1[7][1].c[2],records1[7][1].c[3]);
//	    for(i=0;i<4;i++)
//		{
//			printf("7 1 %d:",i);
//			for(j=0;j<records1[7][1].c[i];j++)
//				printf("%d ",records1[7][1].serial_num[i][j]);
//			printf("\n");
//		}
}
