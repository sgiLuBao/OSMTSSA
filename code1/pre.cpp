struct node33
{
	double pos,s,e;
}xx,yy;
struct node44
{
	double sx,sy,ex,ey;
}xx_45,xx_135;
void pre(int s,int e)
{
    int i,k,sp,m,flag,cc;
	double x1,x2,y1,y2,fx,fy,midx,midy,p,q,crop,cro_point[2][2];
	double l,r,t,b;
    for(k=0;k<4;k++)
	{
       records1[s][e].c[k]=0;
	   records1[e][s].c[k]=0;
	}
		   for(sp=0;sp<=3;sp++)
		   {
			  x1=graph[s][0];
		      y1=graph[s][1];
		      x2=graph[e][0];
		      y2=graph[e][1];
		      fx=fabs(x1-x2);
		      fy=fabs(y1-y2);
			  m=sp;
			  xx.pos=-1;xx.s=-1;xx.e=-1;
              yy.pos=-1;yy.s=-1;yy.e=-1;
			  xx_45.sx=999999999;xx_45.sy=999999999;xx_45.ex=999999999;xx_45.ey=999999999;
              xx_135.sx=999999999;xx_135.sy=999999999;xx_135.ex=999999999;xx_135.ey=999999999;
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
                        xx.pos=y1; 
				        yy.pos=x1;
					 }
			         else
					 {
				        xx.pos=y2;
				        yy.pos=x2;
					 }
			   	     if(x1>x2)
					 {
				        xx.s=x2; 
				        xx.e=x1; 
					 }
			         else
					 {
                       xx.s=x1;
				       xx.e=x2;
					 }
			        if(y1>y2)
					{
				       yy.s=y2; 
				       yy.e=y1; 
					}
			        else 
					{
                       yy.s=y1;
			  	       yy.e=y2;
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
					      xx.pos=y1;
				 	      xx.s=x1;
					      xx.e=x2-fy;
					      if(y1<y2) 
						  { 
						    xx_45.sx=x2-fy;
						    xx_45.sy=y1;
						    xx_45.ex=x2;
						    xx_45.ey=y2;
						  }
					      else  
						  {
                            xx_135.sx=x2-fy;
						    xx_135.sy=y1;
						    xx_135.ex=x2;
						    xx_135.ey=y2;
						  }
					   }
				       else 
					   {
					     xx.pos=y2;
					     xx.s=x1+fy;
					     xx.e=x2;
					     if(y1<y2)
						 {
                      	   xx_45.sx=x1;
						   xx_45.sy=y1;
						   xx_45.ex=x1+fy;
						   xx_45.ey=y2;
						 }
					     else
						 {
                           xx_135.sx=x1;
						   xx_135.sy=y1;
						   xx_135.ex=x1+fy;
						   xx_135.ey=y2;
						 }
					   }
					 }
				     else 
					 {
                         if(m==0) 
						 {
					       yy.pos=x1;
					       if(y1<y2)
						   {
					     	 xx_45.sx=x1;
						     xx_45.sy=y2-fx;
						     xx_45.ex=x2;
						     xx_45.ey=y2;
						     yy.s=y1;
					         yy.e=y2-fx;
						   }
					       else
						   { 
                             xx_135.sx=x1;
						     xx_135.sy=y2+fx;
						     xx_135.ex=x2;
					      	 xx_135.ey=y2;
					 	     yy.s=y2+fx;
					         yy.e=y1;
						   }
						 }
				         else
						 {
					         yy.pos=x2;
					         if(y1<y2)
							 {
                             	xx_45.sx=x1;
					          	xx_45.sy=y1;
					        	xx_45.ex=x2;
					          	xx_45.ey=y1+fx;
					        	yy.s=y1+fx;
				   	            yy.e=y2;
							 }
					         else
							 {
                                xx_135.sx=x1;
						        xx_135.sy=y1;
						        xx_135.ex=x2;
						        xx_135.ey=y1-fx;
						        yy.s=y2;
					            yy.e=y1-fx;
							 }
						 }
					 }
				  } 
			  }
			  if(m==2||m==3)  
			  {
			       if(m==2)
				   {
				      xx.pos=y2; 
				      yy.pos=x1; 
				   }
			       else 
				   {
			          xx.pos=y1;
				      yy.pos=x2;
				   }
			       if(x1>x2)
				   {
				      xx.s=x2; 
				      xx.e=x1; 
				   }
		           else
				   {
                      xx.s=x1;
				      xx.e=x2;
				   }
			       if(y1>y2)
				   {
				      yy.s=y2; 
				      yy.e=y1; 
				   }
			       else 
				   {
                      yy.s=y1;
				      yy.e=y2;
				   }
			  }
			  
//			  if(sp==0&&i==3&&j==72) {
//				  printf("%lf %lf\n%lf %lf\n",x1,y1,x2,y2);
//				  printf("%d\n",m);
//				  printf("x:%lf %lf %lf\n y:%lf %lf %lf\n",xx.pos,xx.s,xx.e,yy.pos,yy.s,yy.e);
//			     printf("45:%lf %lf %lf %lf\n135:%lf %lf %lf %lf\n",xx_45.sx,xx_45.sy,xx_45.ex,xx_45.ey,xx_135.sx,xx_135.sy,xx_135.ex,xx_135.ey);
//			  }
     
			  for(k=1;k<=barr_num;k++)
			  {	             
				if(barr[k][0]>=r||barr[k][1]>=t||barr[k][2]<=l||barr[k][3]<=b) continue;

			    if(xx.pos!=-1&&xx.e!=-1&&xx.s!=-1&&!(xx.pos<=barr[k][1]||xx.pos>=barr[k][3]||xx.e<=barr[k][0]||xx.s>=barr[k][2]))//如果水平线完全在矩形之下或之上或之左或之右，则不相交
				{
                   records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;				  
				   records1[s][e].c[sp]++;
				   continue;
				}

			    if(yy.e!=-1&&yy.pos!=-1&&yy.s!=-1&&!(yy.pos<=barr[k][0]||yy.pos>=barr[k][2]||yy.e<=barr[k][1]||yy.s>=barr[k][3]))//如果垂直线完全在矩形之左或之右或之下或之上，则不相交
				{
				   records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				   records1[s][e].c[sp]++;
				   continue;
				}
			    
			    if(xx_45.sx!=999999999&&xx_45.sy!=999999999&&xx_45.ex!=999999999&&xx_45.ey!=999999999)
				{
                   if((xx_45.sx>barr[k][0]&&xx_45.sx<barr[k][2]&&xx_45.sy>barr[k][1]&&xx_45.sy<barr[k][3])||(xx_45.ex>barr[k][0]&&xx_45.ex<barr[k][2]&&xx_45.ey>barr[k][1]&&xx_45.ey<barr[k][3]))//如果45度斜边有一个顶点在矩形内，则肯定相交
				   {
					  records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				      records1[s][e].c[sp]++;
				      continue; 				       
				   }
				   else
				   {
			         flag=0;
			         cc=0;  
			         p=(xx_45.ey-xx_45.sy)/(xx_45.ex-xx_45.sx); 
			         q=xx_45.sy-p*xx_45.sx;
	               
                     crop=(barr[k][1]-q)/p; 
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=xx_45.sx&&crop<=xx_45.ex) 
					 { 
			     	    flag++; 
				        if(cc<2)
						{ 
				           cro_point[cc][0]=crop;
				           cro_point[cc++][1]=barr[k][1];
						}
					 }
			         crop=(barr[k][3]-q)/p;
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=xx_45.sx&&crop<=xx_45.ex) 
					 { 
			    	    flag++;
			            if(cc<2)
						{
			               cro_point[cc][0]=crop;
			               cro_point[cc++][1]=barr[k][3];
						}
					 }
		             crop=p*barr[k][0]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=xx_45.sy&&crop<=xx_45.ey)
					 {
				       flag++;
				       if(cc<2)
					   {
				         cro_point[cc][0]=barr[k][0];
				         cro_point[cc++][1]=crop;
					   }
					 }
			         crop=p*barr[k][2]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=xx_45.sy&&crop<=xx_45.ey)
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
					  records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				      records1[s][e].c[sp]++;
				      continue; 
					 }
			         
					 if(flag==2)
					 { 
                        if(!(cro_point[0][0]==cro_point[1][0]&&cro_point[0][1]==cro_point[1][1]))
						{
						   records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				           records1[s][e].c[sp]++;
				           continue; 
						}
					 }
				   }
				}
				if(xx_135.ex!=999999999&&xx_135.ey!=999999999&&xx_135.sx!=999999999&&xx_135.sy!=999999999)
				{
                   if((xx_135.sx>barr[k][0]&&xx_135.sx<barr[k][2]&&xx_135.sy>barr[k][1]&&xx_135.sy<barr[k][3])||(xx_135.ex>barr[k][0]&&xx_135.ex<barr[k][2]&&xx_135.ey>barr[k][1]&&xx_135.ey<barr[k][3])) //如果135度斜边有一个顶点在矩形内，则肯定相交
				   {
					  records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				      records1[s][e].c[sp]++;
				      continue; 		       
				   }
			       else
				   {
			         flag=0; 
			         cc=0;  
			         p=(xx_135.ey-xx_135.sy)/(xx_135.ex-xx_135.sx); 
			         q=xx_135.sy-p*xx_135.sx;
		             
                     crop=(barr[k][1]-q)/p; 
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=xx_135.sx&&crop<=xx_135.ex) 
					 { 
			           flag++; 
			           if(cc<2)
					   {
			            cro_point[cc][0]=crop;
				        cro_point[cc++][1]=barr[k][1];
					   }
					 }
			         crop=(barr[k][3]-q)/p;
			         if(crop>=barr[k][0]&&crop<=barr[k][2]&&crop>=xx_135.sx&&crop<=xx_135.ex) 
					 {
				        flag++;
				        if(cc<2)
						{
				         cro_point[cc][0]=crop;
			             cro_point[cc++][1]=barr[k][3];
						}
					 }
		             crop=p*barr[k][0]+q;
			         if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=xx_135.ey&&crop<=xx_135.sy)
					 { 
				        flag++;
				        if(cc<2)
						{
			               cro_point[cc][0]=barr[k][0];
				           cro_point[cc++][1]=crop;
						}
					 }
			        crop=p*barr[k][2]+q;
			        if(crop>=barr[k][1]&&crop<=barr[k][3]&&crop>=xx_135.ey&&crop<=xx_135.sy)
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
					  records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				      records1[s][e].c[sp]++;
				      continue; 
					}
			        if(flag==2)
					{ 
                      if(!(cro_point[0][0]==cro_point[1][0]&&cro_point[0][1]==cro_point[1][1])) 
					  { 
						 records1[s][e].serial_num[sp][records1[s][e].c[sp]]=k;
				         records1[s][e].c[sp]++;
				         continue; 
					  }
					}
				   }
				}
			 }
			 if(sp==2)
			 {
               records1[e][s].c[3]=records1[s][e].c[sp];
			   for(i=0;i<records1[s][e].c[sp];i++)
                records1[e][s].serial_num[3][i]=records1[s][e].serial_num[sp][i];
			   if(records1[s][e].c[sp]==0) CH=2;
			 }
			 else if(sp==3)
			 {
               records1[e][s].c[2]=records1[s][e].c[sp];
			   for(i=0;i<records1[s][e].c[sp];i++)
                records1[e][s].serial_num[2][i]=records1[s][e].serial_num[sp][i];
			   if(records1[s][e].c[sp]==0) CH=3;
			 }
			 else if(sp==0)
			 {
               records1[e][s].c[1]=records1[s][e].c[sp];
			   for(i=0;i<records1[s][e].c[sp];i++)
                records1[e][s].serial_num[1][i]=records1[s][e].serial_num[sp][i];
			    if(records1[s][e].c[sp]==0) CH=0;
			 }
			 else 
			 {
               records1[e][s].c[0]=records1[s][e].c[sp];
			   for(i=0;i<records1[s][e].c[sp];i++)
                records1[e][s].serial_num[0][i]=records1[s][e].serial_num[sp][i];
			    if(records1[s][e].c[sp]==0) CH=1;
			 }
         }
}