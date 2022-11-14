struct final
{
	double pos;
	double s;
	double e;
}xxsegment[2000],yysegment[2000],rr_x[2000],rr_y[2000];
bool ccon(struct final a,struct final b)
{
	if(a.pos<b.pos) return true;
	else if(a.pos==b.pos) return a.s<b.s;
	else return false;
}
void count_length()
{
	int ind,sp;
	int n1=0,n2=0,n3=0,n4=0;
	int i,sum=0;
	for(i=1;;i++)
	{
       if(edge[i].mark==false) continue;
	   if(sum==vertice-1) break;
	   sum++;
	   sp=edge[i].c;
	   ind=edge[i].index;
	//   printf("µÚ%dÌõ±ß£º\n",i);
	   if(records2[ind][sp].mark[0]==true) 
	   {
          xxsegment[n1].pos=records2[ind][sp].posh;
		  xxsegment[n1].s=records2[ind][sp].sh;
		  xxsegment[n1++].e=records2[ind][sp].eh;
	//	  printf("hor:%lf %lf %lf\n",records2[ind][sp].posh,records2[ind][sp].sh,records2[ind][sp].eh);
		}
	   if(records2[ind][sp].mark[1]==true) 
	   {
          yysegment[n2].pos=records2[ind][sp].posv;
		  yysegment[n2].s=records2[ind][sp].sv;
		  yysegment[n2++].e=records2[ind][sp].ev;
	//	  printf("ver:%lf %lf %lf\n",records2[ind][sp].posv,records2[ind][sp].sv,records2[ind][sp].ev);
		}   
       if(records2[ind][sp].mark[2]==true) 
	   {
         
		  rr_x[n3].pos=records2[ind][sp].pos45;

		  rr_x[n3].s=records2[ind][sp].s45;

		  rr_x[n3++].e=records2[ind][sp].e45;

  //	   printf("45:%lf %lf %lf\n",records2[ind][sp].pos45,records2[ind][sp].s45,records2[ind][sp].e45);
		}
	   if(records2[ind][sp].mark[3]==true) 
	   {
          rr_y[n4].pos=records2[ind][sp].pos135;
		  rr_y[n4].s=records2[ind][sp].s135;
		  rr_y[n4++].e=records2[ind][sp].e135;
	//	  printf("135:%lf %lf %lf\n",records2[ind][sp].pos135,records2[ind][sp].s135,records2[ind][sp].e135);
	   }
	}
//			 for(i=0;i<n4;i++)
//				 printf("%lf %lf %lf\n",rr_y[i].pos,rr_y[i].s,rr_y[i].e);
	          sort(xxsegment,xxsegment+n1,ccon);  
	          sort(yysegment,yysegment+n2,ccon);
	          sort(rr_x,rr_x+n3,ccon);
	          sort(rr_y,rr_y+n4,ccon);
			  for(i=1;i<n1;i++) 
			  {
		          if(xxsegment[i].pos==xxsegment[i-1].pos)
			      if(xxsegment[i].s==xxsegment[i-1].s)
				  {
				     if(xxsegment[i].e<xxsegment[i-1].e)
						 xxsegment[i].e=xxsegment[i-1].e;
				     xxsegment[i-1].pos=0;
				     xxsegment[i-1].s=0;
				     xxsegment[i-1].e=0;
				  }
			      else 
				  {
				     if(xxsegment[i].s<xxsegment[i-1].e)
					 {				        
			   	        if(xxsegment[i].e<xxsegment[i-1].e)
						   xxsegment[i].e=xxsegment[i-1].e;
						xxsegment[i].s=xxsegment[i-1].s;
				        xxsegment[i-1].pos=0;
			 	        xxsegment[i-1].s=0;
				        xxsegment[i-1].e=0;
					 }
				  }
			  }
			  for(i=1;i<n2;i++) 
			  {
		         if(yysegment[i].pos==yysegment[i-1].pos)
			     if(yysegment[i].s==yysegment[i-1].s)
				 {
				    if(yysegment[i].e<yysegment[i-1].e)
					   yysegment[i].e=yysegment[i-1].e;
			    	yysegment[i-1].pos=0;
				    yysegment[i-1].s=0;
				    yysegment[i-1].e=0;
				 }
			     else 
				 {
			    	if(yysegment[i].s<yysegment[i-1].e)
					{				    	
			    	    if(yysegment[i].e<yysegment[i-1].e)
					       yysegment[i].e=yysegment[i-1].e;
						yysegment[i].s=yysegment[i-1].s;
				        yysegment[i-1].pos=0;
				        yysegment[i-1].s=0;
				        yysegment[i-1].e=0;
					}
				 }
			  }
              for(i=1;i<n3;i++)
			  {
		         if(rr_x[i].pos==rr_x[i-1].pos)
			     if(rr_x[i].s==rr_x[i-1].s)
				 {
				    if(rr_x[i].e<rr_x[i-1].e)
						rr_x[i].e=rr_x[i-1].e;
				    rr_x[i-1].pos=0;
				    rr_x[i-1].s=0;
				    rr_x[i-1].e=0;
				 }
			     else 
				 {
				    if(rr_x[i].s<rr_x[i-1].e)
					{					   
				       if(rr_x[i].e<rr_x[i-1].e)
					     rr_x[i].e=rr_x[i-1].e;
					   rr_x[i].s=rr_x[i-1].s;
				       rr_x[i-1].pos=0;
				       rr_x[i-1].s=0;
				       rr_x[i-1].e=0;
					}
				 }
			  }
              for(i=1;i<n4;i++) 
			  {
		          if(rr_y[i].pos==rr_y[i-1].pos)
			      if(rr_y[i].s==rr_y[i-1].s)
				  {
				     if(rr_y[i].e<rr_y[i-1].e)
					   rr_y[i].e=rr_y[i-1].e;
				     rr_y[i-1].pos=0;
				     rr_y[i-1].s=0;
				     rr_y[i-1].e=0;
				  }
			      else 
				  {
				     if(rr_y[i].s<rr_y[i-1].e)
					 {					   
				       if(rr_y[i].e<rr_y[i-1].e)
				  	     rr_y[i].e=rr_y[i-1].e;
					   rr_y[i].s=rr_y[i-1].s;
			    	   rr_y[i-1].pos=0;
			           rr_y[i-1].s=0;
				       rr_y[i-1].e=0;
					 }
				  }
			  }
			  final_len=0;
              for(i=0;i<n1;i++)
	            final_len+=(xxsegment[i].e-xxsegment[i].s);
	          for(i=0;i<n2;i++)
	            final_len+=(yysegment[i].e-yysegment[i].s);
	          for(i=0;i<n3;i++)
	            final_len+=(rr_x[i].e-rr_x[i].s);
	          for(i=0;i<n4;i++)
	            final_len+=(rr_y[i].e-rr_y[i].s);
}