struct node1
{
	double pos;
	double s;
	double e;
}xsegment[1010],ysegment[1010],r_x[1010],r_y[1010];//���߶�[y���� ����� ���յ�],���߶�[x���� ����� ���յ�]
struct node2
{
	double sx;
	double sy;
	double ex;
	double ey;
}x45[1010],x135[1010];//б�߶�[������꣬�յ�����]
bool cmp1(struct node1 a,struct node1 b)
{
	if(a.pos<b.pos) return true;
	else return false;
}
bool cmp2(struct node1 a,struct node1 b)
{
	if(a.s<b.s) return true;
	else return false;
}
double Getfitness()
{
    int i,k,sp,xt=0,yt=0,x45t=0,x135t=0,rxt=0,ryt=0;
	double x1,x2,y1,y2,fx,fy,fitness=0,midx,midy;
//	printf("%d\n",vertice);
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",min_tree[i]);
//	printf("\n");
	for(i=1;i<vertice;i++)
	{
        x1=graph[min_tree[i*3-2]][0]; //���x
		y1=graph[min_tree[i*3-2]][1]; //���y
		x2=graph[min_tree[i*3-1]][0]; //�յ�x
		y2=graph[min_tree[i*3-1]][1]; //�յ�y
		sp=min_tree[i*3]; //���ӷ�ʽ
		fx=fabs(x1-x2);  //ˮƽ����
		fy=fabs(y1-y2);  //��ֱ����
//		printf("%lf %lf %lf %lf %d %lf %lf\n",x1,y1,x2,y2,sp,fx,fy);
        if(sp==2||sp==3)  //���߶�Ϊ����������ʱ
		{
			if(sp==2)
			{
				xsegment[xt].pos=y2; //ˮƽ��������
				ysegment[yt].pos=x1; //��ֱ�ߺ�����
			}
			else 
			{
			    xsegment[xt].pos=y1;
				ysegment[yt].pos=x2;
			}
			if(x1>x2)
			{
				xsegment[xt].s=x2; //ˮƽ������������
				xsegment[xt++].e=x1; //ˮƽ�����յ������
			}
			else
			{
                xsegment[xt].s=x1;
				xsegment[xt++].e=x2;
			}
			if(y1>y2)
			{
				ysegment[yt].s=y2; //��ֱ�������������
				ysegment[yt++].e=y1; //��ֱ�����յ�������
			}
			else 
			{
                ysegment[yt].s=y1;
				ysegment[yt++].e=y2;
			}
		}
		if(sp==0||sp==1) //���߶ε����ӷ�ʽΪ�������ٽṹʱ
		{
           if(fx==0||fy==0) //���㹲�ߵ����
		   {
			   if(sp==0)
			   {
                  xsegment[xt].pos=y1; 
				  ysegment[yt].pos=x1;
			   }
			   else
			   {
				   xsegment[xt].pos=y2;
				   ysegment[yt].pos=x2;
			   }
			   	if(x1>x2)
				{
				   xsegment[xt].s=x2; //ˮƽ������������
				   xsegment[xt++].e=x1; //ˮƽ�����յ������
				}
			    else
				{
                   xsegment[xt].s=x1;
				   xsegment[xt++].e=x2;
				}
			    if(y1>y2)
				{
				   ysegment[yt].s=y2; //��ֱ�������������
				   ysegment[yt++].e=y1; //��ֱ�����յ�������
				}
			    else 
				{
                   ysegment[yt].s=y1;
			  	   ysegment[yt++].e=y2;
				}
		   }
		   else //���㲻����
		   {
                if(x1>x2) //���������յ��Ҷ��򽻻�λ��
				{
					midx=x1;
					midy=y1;
					x1=x2;
					y1=y2;
					x2=midx;
                    y2=midy;
					sp=!sp;
				}
                if(fx>fy) //ˮƽ�����ڴ�ֱ�������
				{
				  if(sp==0) //0���ӷ�ʽ
				  {
					xsegment[xt].pos=y1;
					xsegment[xt].s=x1;
					xsegment[xt++].e=x2-fy;
					if(y1<y2) //��¼45���߶ε������յ�����
					{
						x45[x45t].sx=x2-fy;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
					}
					else  //��¼135���߶ε������յ�����
					{
                        x135[x135t].sx=x2-fy;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					}
				  }
				  else //1���ӷ�ʽ
				  {
					xsegment[xt].pos=y2;
					xsegment[xt].s=x1+fy;
					xsegment[xt++].e=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x1+fy;
						x45[x45t++].ey=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x1+fy;
						x135[x135t++].ey=y2;
					}
				  }
				}
				else //��ֱ�����ڻ����ˮƽ�������
				{
                  if(sp==0) 
				  {
					ysegment[yt].pos=x1;
					if(y1<y2)
					{
						x45[x45t].sx=x1;
						x45[x45t].sy=y2-fx;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
						ysegment[yt].s=y1;
					    ysegment[yt++].e=y2-fx;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y2+fx;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					 	ysegment[yt].s=y1;
					    ysegment[yt++].e=y2+fx;
					}
				  }
				  else
				  {
					ysegment[yt].pos=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y1+fx;
						ysegment[yt].s=y1+fx;
				   	    ysegment[yt++].e=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y1-fx;
						ysegment[yt].s=y1-fx;
					    ysegment[yt++].e=y2;
					}
				  }
				}
		   }
		} 
//		printf("%d %d %d %d\n",xt,yt,x45t,x135t);
	}
	for(i=0;i<x45t;i++) //��45������ʱ����ת45�ȱ�Ϊˮƽ��������xsegment��
	{
		r_x[rxt].pos=P*(x45[i].sy-x45[i].sx); //��ת��Ĵ�ֱ����
		r_x[rxt].s=P*(x45[i].sx+x45[i].sy);   //��ת������
		r_x[rxt++].e=P*(x45[i].ex+x45[i].ey); //��ת����յ�
	}
	for(i=0;i<x135t;i++)//��135������ʱ����ת45�ȱ�Ϊ��ֱ��������ysegment��
	{
        r_y[ryt].pos=P*(x135[i].sx+x135[i].sy); 
		r_y[ryt].s=P*(x135[i].sy-x135[i].sx);
		r_y[ryt++].e=P*(x135[i].ey-x135[i].ex);
	}
	for(i=0;i<xt;i++) //����ˮƽ�߶Σ�ʹ����������յ�����
	{
		if(xsegment[i].s>xsegment[i].e)
		{
			midx=xsegment[i].s;
			xsegment[i].s=xsegment[i].e;
			xsegment[i].e=midx;
		}
	}
	for(i=0;i<yt;i++)
	{
       if(ysegment[i].s>ysegment[i].e)
	   {
		   midy=ysegment[i].s;
		   ysegment[i].s=ysegment[i].e;
		   ysegment[i].e=midy;
	   }
	}
	for(i=0;i<rxt;i++)
	{
		if(r_x[i].s>r_x[i].e)
		{
			midx=r_x[i].s;
			r_x[i].s=r_x[i].e;
			r_x[i].e=midx;
		}
	}
	for(i=0;i<ryt;i++)
	{
		if(r_y[i].s>r_y[i].e)
		{
			midx=r_y[i].s;
			r_y[i].s=r_y[i].e;
			r_y[i].e=midx;
		}
	}
	sort(xsegment,xsegment+xt,cmp1);  //���յ�һ�е���������
	sort(ysegment,ysegment+yt,cmp1);
	sort(r_x,r_x+rxt,cmp1);
	sort(r_y,r_y+ryt,cmp1);
	for(i=1;i<xt;i++)//ˮƽ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
        k=i-1;
		while(i<xt&&xsegment[i].pos==xsegment[i-1].pos)
			i++;
		sort(xsegment+k,xsegment+i,cmp2);
	}
	for(i=1;i<yt;i++)//��ֱ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
        k=i-1;
		while(i<yt&&ysegment[i].pos==ysegment[i-1].pos)
			i++;
		sort(ysegment+k,ysegment+i,cmp2);
	}
	for(i=1;i<rxt;i++)//��ת���ˮƽ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
        k=i-1;
		while(i<rxt&&r_x[i].pos==r_x[i-1].pos)
			i++;
		sort(r_x+k,r_x+i,cmp2);
	}
    for(i=1;i<ryt;i++)//��ת��Ĵ�ֱ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
        k=i-1;
		while(i<ryt&&r_y[i].pos==r_y[i-1].pos)
			i++;
		sort(r_y+k,r_y+i,cmp2);
	}
	for(i=1;i<xt;i++) //�ϲ��ص���ˮƽ��
	{
		if(xsegment[i].pos==xsegment[i-1].pos)
			if(xsegment[i].s==xsegment[i-1].s)
			{
				if(xsegment[i].e<xsegment[i-1].e)
					xsegment[i].e=xsegment[i-1].e;
				xsegment[i-1].pos=0;
				xsegment[i-1].s=0;
				xsegment[i-1].e=0;
			}
			else 
			{
				if(xsegment[i].s<xsegment[i-1].e)
				{
				   xsegment[i].s=xsegment[i-1].s;
			   	   if(xsegment[i].e<xsegment[i-1].e)
				  	 xsegment[i].e=xsegment[i-1].e;
				   xsegment[i-1].pos=0;
			 	   xsegment[i-1].s=0;
				   xsegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<yt;i++) //�ϲ��ص��Ĵ�ֱ��
	{
		if(ysegment[i].pos==ysegment[i-1].pos)
			if(ysegment[i].s==ysegment[i-1].s)
			{
				if(ysegment[i].e<ysegment[i-1].e)
					ysegment[i].e=ysegment[i-1].e;
				ysegment[i-1].pos=0;
				ysegment[i-1].s=0;
				ysegment[i-1].e=0;
			}
			else 
			{
				if(ysegment[i].s<ysegment[i-1].e)
				{
					ysegment[i].s=ysegment[i-1].s;
			    	if(ysegment[i].e<ysegment[i-1].e)
					  ysegment[i].e=ysegment[i-1].e;
				    ysegment[i-1].pos=0;
				    ysegment[i-1].s=0;
				    ysegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<rxt;i++) //�ϲ���ת���ص���ˮƽ��
	{
		if(r_x[i].pos==r_x[i-1].pos)
			if(r_x[i].s==r_x[i-1].s)
			{
				if(r_x[i].e<r_x[i-1].e)
					r_x[i].e=r_x[i-1].e;
				r_x[i-1].pos=0;
				r_x[i-1].s=0;
				r_x[i-1].e=0;
			}
			else 
			{
				if(r_x[i].s<r_x[i-1].e)
				{
					r_x[i].s=r_x[i-1].s;
				    if(r_x[i].e<r_x[i-1].e)
					  r_x[i].e=r_x[i-1].e;
				    r_x[i-1].pos=0;
				    r_x[i-1].s=0;
				    r_x[i-1].e=0;
				}
			}
	}
	for(i=1;i<ryt;i++) //�ϲ���ת���ص��Ĵ�ֱ��
	{
		if(r_y[i].pos==r_y[i-1].pos)
			if(r_y[i].s==r_y[i-1].s)
			{
				if(r_y[i].e<r_y[i-1].e)
					r_y[i].e=r_y[i-1].e;
				r_y[i-1].pos=0;
				r_y[i-1].s=0;
				r_y[i-1].e=0;
			}
			else 
			{
				if(r_y[i].s<r_y[i-1].e)
				{
					r_y[i].s=r_y[i-1].s;
				    if(r_y[i].e<r_y[i-1].e)
				  	  r_y[i].e=r_y[i-1].e;
			    	r_y[i-1].pos=0;
			    	r_y[i-1].s=0;
				    r_y[i-1].e=0;
				}
			}
	}

//		printf("\nx:\n");
//	for(i=0;i<xt;i++)
//		printf("%.0lf %.0lf %.0lf\n",xsegment[i].pos,xsegment[i].s,xsegment[i].e);
//	printf("\ny:\n");
// 	for(i=0;i<yt;i++)
//	printf("%.0lf %.0lf %.0lf\n",ysegment[i].pos,ysegment[i].s,ysegment[i].e);
//	printf("\nrx:\n");
// 	for(i=0;i<rxt;i++)
//	printf("%lf %lf %lf\n",r_x[i].pos,r_x[i].s,r_x[i].e);
//	printf("\nry:\n");
//  for(i=0;i<ryt;i++)
//	printf("%lf %lf %lf\n",r_y[i].pos,r_y[i].s,r_y[i].e);
	for(i=0;i<xt;i++)
	  fitness+=(xsegment[i].e-xsegment[i].s);
	for(i=0;i<yt;i++)
	  fitness+=(ysegment[i].e-ysegment[i].s);
	for(i=0;i<rxt;i++)
	  fitness+=(r_x[i].e-r_x[i].s);
	for(i=0;i<ryt;i++)
	  fitness+=(r_y[i].e-r_y[i].s);
//	printf("%lf\n",fitness);
	return fitness;
}
double Getfitness2()
{
	int i, k, sp, xt = 0, yt = 0, x45t = 0, x135t = 0, rxt = 0, ryt = 0;
	double x1, x2, y1, y2, fx, fy, fitness = 0, midx, midy;
	//	printf("%d\n",vertice);
	//	for(i=1;i<=3*(vertice-1);i++)
	//		printf("%d ",min_tree[i]);
	//	printf("\n");
	for (i = 1; i<vertice; i++)
	{
		x1 = graph[min_tree2[i * 3 - 2]][0]; //���x
		y1 = graph[min_tree2[i * 3 - 2]][1]; //���y
		x2 = graph[min_tree2[i * 3 - 1]][0]; //�յ�x
		y2 = graph[min_tree2[i * 3 - 1]][1]; //�յ�y
		sp = min_tree2[i * 3]; //���ӷ�ʽ
		fx = fabs(x1 - x2);  //ˮƽ����
		fy = fabs(y1 - y2);  //��ֱ����
							 //		printf("%lf %lf %lf %lf %d %lf %lf\n",x1,y1,x2,y2,sp,fx,fy);
		if (sp == 2 || sp == 3)  //���߶�Ϊ����������ʱ
		{
			if (sp == 2)
			{
				xsegment[xt].pos = y2; //ˮƽ��������
				ysegment[yt].pos = x1; //��ֱ�ߺ�����
			}
			else
			{
				xsegment[xt].pos = y1;
				ysegment[yt].pos = x2;
			}
			if (x1>x2)
			{
				xsegment[xt].s = x2; //ˮƽ������������
				xsegment[xt++].e = x1; //ˮƽ�����յ������
			}
			else
			{
				xsegment[xt].s = x1;
				xsegment[xt++].e = x2;
			}
			if (y1>y2)
			{
				ysegment[yt].s = y2; //��ֱ�������������
				ysegment[yt++].e = y1; //��ֱ�����յ�������
			}
			else
			{
				ysegment[yt].s = y1;
				ysegment[yt++].e = y2;
			}
		}
		if (sp == 0 || sp == 1) //���߶ε����ӷ�ʽΪ�������ٽṹʱ
		{
			if (fx == 0 || fy == 0) //���㹲�ߵ����
			{
				if (sp == 0)
				{
					xsegment[xt].pos = y1;
					ysegment[yt].pos = x1;
				}
				else
				{
					xsegment[xt].pos = y2;
					ysegment[yt].pos = x2;
				}
				if (x1>x2)
				{
					xsegment[xt].s = x2; //ˮƽ������������
					xsegment[xt++].e = x1; //ˮƽ�����յ������
				}
				else
				{
					xsegment[xt].s = x1;
					xsegment[xt++].e = x2;
				}
				if (y1>y2)
				{
					ysegment[yt].s = y2; //��ֱ�������������
					ysegment[yt++].e = y1; //��ֱ�����յ�������
				}
				else
				{
					ysegment[yt].s = y1;
					ysegment[yt++].e = y2;
				}
			}
			else //���㲻����
			{
				if (x1>x2) //���������յ��Ҷ��򽻻�λ��
				{
					midx = x1;
					midy = y1;
					x1 = x2;
					y1 = y2;
					x2 = midx;
					y2 = midy;
					sp = !sp;
				}
				if (fx>fy) //ˮƽ�����ڴ�ֱ�������
				{
					if (sp == 0) //0���ӷ�ʽ
					{
						xsegment[xt].pos = y1;
						xsegment[xt].s = x1;
						xsegment[xt++].e = x2 - fy;
						if (y1<y2) //��¼45���߶ε������յ�����
						{
							x45[x45t].sx = x2 - fy;
							x45[x45t].sy = y1;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y2;
						}
						else  //��¼135���߶ε������յ�����
						{
							x135[x135t].sx = x2 - fy;
							x135[x135t].sy = y1;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y2;
						}
					}
					else //1���ӷ�ʽ
					{
						xsegment[xt].pos = y2;
						xsegment[xt].s = x1 + fy;
						xsegment[xt++].e = x2;
						if (y1<y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y1;
							x45[x45t].ex = x1 + fy;
							x45[x45t++].ey = y2;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y1;
							x135[x135t].ex = x1 + fy;
							x135[x135t++].ey = y2;
						}
					}
				}
				else //��ֱ�����ڻ����ˮƽ�������
				{
					if (sp == 0)
					{
						ysegment[yt].pos = x1;
						if (y1<y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y2 - fx;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y2;
							ysegment[yt].s = y1;
							ysegment[yt++].e = y2 - fx;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y2 + fx;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y2;
							ysegment[yt].s = y1;
							ysegment[yt++].e = y2 + fx;
						}
					}
					else
					{
						ysegment[yt].pos = x2;
						if (y1<y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y1;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y1 + fx;
							ysegment[yt].s = y1 + fx;
							ysegment[yt++].e = y2;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y1;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y1 - fx;
							ysegment[yt].s = y1 - fx;
							ysegment[yt++].e = y2;
						}
					}
				}
			}
		}
		//		printf("%d %d %d %d\n",xt,yt,x45t,x135t);
	}
	for (i = 0; i<x45t; i++) //��45������ʱ����ת45�ȱ�Ϊˮƽ��������xsegment��
	{
		r_x[rxt].pos = P*(x45[i].sy - x45[i].sx); //��ת��Ĵ�ֱ����
		r_x[rxt].s = P*(x45[i].sx + x45[i].sy);   //��ת������
		r_x[rxt++].e = P*(x45[i].ex + x45[i].ey); //��ת����յ�
	}
	for (i = 0; i<x135t; i++)//��135������ʱ����ת45�ȱ�Ϊ��ֱ��������ysegment��
	{
		r_y[ryt].pos = P*(x135[i].sx + x135[i].sy);
		r_y[ryt].s = P*(x135[i].sy - x135[i].sx);
		r_y[ryt++].e = P*(x135[i].ey - x135[i].ex);
	}
	for (i = 0; i<xt; i++) //����ˮƽ�߶Σ�ʹ����������յ�����
	{
		if (xsegment[i].s>xsegment[i].e)
		{
			midx = xsegment[i].s;
			xsegment[i].s = xsegment[i].e;
			xsegment[i].e = midx;
		}
	}
	for (i = 0; i<yt; i++)
	{
		if (ysegment[i].s>ysegment[i].e)
		{
			midy = ysegment[i].s;
			ysegment[i].s = ysegment[i].e;
			ysegment[i].e = midy;
		}
	}
	for (i = 0; i<rxt; i++)
	{
		if (r_x[i].s>r_x[i].e)
		{
			midx = r_x[i].s;
			r_x[i].s = r_x[i].e;
			r_x[i].e = midx;
		}
	}
	for (i = 0; i<ryt; i++)
	{
		if (r_y[i].s>r_y[i].e)
		{
			midx = r_y[i].s;
			r_y[i].s = r_y[i].e;
			r_y[i].e = midx;
		}
	}
	sort(xsegment, xsegment + xt, cmp1);  //���յ�һ�е���������
	sort(ysegment, ysegment + yt, cmp1);
	sort(r_x, r_x + rxt, cmp1);
	sort(r_y, r_y + ryt, cmp1);
	for (i = 1; i<xt; i++)//ˮƽ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
		k = i - 1;
		while (i<xt&&xsegment[i].pos == xsegment[i - 1].pos)
			i++;
		sort(xsegment + k, xsegment + i, cmp2);
	}
	for (i = 1; i<yt; i++)//��ֱ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
		k = i - 1;
		while (i<yt&&ysegment[i].pos == ysegment[i - 1].pos)
			i++;
		sort(ysegment + k, ysegment + i, cmp2);
	}
	for (i = 1; i<rxt; i++)//��ת���ˮƽ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
		k = i - 1;
		while (i<rxt&&r_x[i].pos == r_x[i - 1].pos)
			i++;
		sort(r_x + k, r_x + i, cmp2);
	}
	for (i = 1; i<ryt; i++)//��ת��Ĵ�ֱ���ڵ�һ������Ļ����ϣ��ٰ��յڶ�����������
	{
		k = i - 1;
		while (i<ryt&&r_y[i].pos == r_y[i - 1].pos)
			i++;
		sort(r_y + k, r_y + i, cmp2);
	}
	for (i = 1; i<xt; i++) //�ϲ��ص���ˮƽ��
	{
		if (xsegment[i].pos == xsegment[i - 1].pos)
			if (xsegment[i].s == xsegment[i - 1].s)
			{
				if (xsegment[i].e<xsegment[i - 1].e)
					xsegment[i].e = xsegment[i - 1].e;
				xsegment[i - 1].pos = 0;
				xsegment[i - 1].s = 0;
				xsegment[i - 1].e = 0;
			}
			else
			{
				if (xsegment[i].s<xsegment[i - 1].e)
				{
					xsegment[i].s = xsegment[i - 1].s;
					if (xsegment[i].e<xsegment[i - 1].e)
						xsegment[i].e = xsegment[i - 1].e;
					xsegment[i - 1].pos = 0;
					xsegment[i - 1].s = 0;
					xsegment[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i<yt; i++) //�ϲ��ص��Ĵ�ֱ��
	{
		if (ysegment[i].pos == ysegment[i - 1].pos)
			if (ysegment[i].s == ysegment[i - 1].s)
			{
				if (ysegment[i].e<ysegment[i - 1].e)
					ysegment[i].e = ysegment[i - 1].e;
				ysegment[i - 1].pos = 0;
				ysegment[i - 1].s = 0;
				ysegment[i - 1].e = 0;
			}
			else
			{
				if (ysegment[i].s<ysegment[i - 1].e)
				{
					ysegment[i].s = ysegment[i - 1].s;
					if (ysegment[i].e<ysegment[i - 1].e)
						ysegment[i].e = ysegment[i - 1].e;
					ysegment[i - 1].pos = 0;
					ysegment[i - 1].s = 0;
					ysegment[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i<rxt; i++) //�ϲ���ת���ص���ˮƽ��
	{
		if (r_x[i].pos == r_x[i - 1].pos)
			if (r_x[i].s == r_x[i - 1].s)
			{
				if (r_x[i].e<r_x[i - 1].e)
					r_x[i].e = r_x[i - 1].e;
				r_x[i - 1].pos = 0;
				r_x[i - 1].s = 0;
				r_x[i - 1].e = 0;
			}
			else
			{
				if (r_x[i].s<r_x[i - 1].e)
				{
					r_x[i].s = r_x[i - 1].s;
					if (r_x[i].e<r_x[i - 1].e)
						r_x[i].e = r_x[i - 1].e;
					r_x[i - 1].pos = 0;
					r_x[i - 1].s = 0;
					r_x[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i<ryt; i++) //�ϲ���ת���ص��Ĵ�ֱ��
	{
		if (r_y[i].pos == r_y[i - 1].pos)
			if (r_y[i].s == r_y[i - 1].s)
			{
				if (r_y[i].e<r_y[i - 1].e)
					r_y[i].e = r_y[i - 1].e;
				r_y[i - 1].pos = 0;
				r_y[i - 1].s = 0;
				r_y[i - 1].e = 0;
			}
			else
			{
				if (r_y[i].s<r_y[i - 1].e)
				{
					r_y[i].s = r_y[i - 1].s;
					if (r_y[i].e<r_y[i - 1].e)
						r_y[i].e = r_y[i - 1].e;
					r_y[i - 1].pos = 0;
					r_y[i - 1].s = 0;
					r_y[i - 1].e = 0;
				}
			}
	}

	//		printf("\nx:\n");
	//	for(i=0;i<xt;i++)
	//		printf("%.0lf %.0lf %.0lf\n",xsegment[i].pos,xsegment[i].s,xsegment[i].e);
	//	printf("\ny:\n");
	// 	for(i=0;i<yt;i++)
	//	printf("%.0lf %.0lf %.0lf\n",ysegment[i].pos,ysegment[i].s,ysegment[i].e);
	//	printf("\nrx:\n");
	// 	for(i=0;i<rxt;i++)
	//	printf("%lf %lf %lf\n",r_x[i].pos,r_x[i].s,r_x[i].e);
	//	printf("\nry:\n");
	//  for(i=0;i<ryt;i++)
	//	printf("%lf %lf %lf\n",r_y[i].pos,r_y[i].s,r_y[i].e);
	for (i = 0; i<xt; i++)
		fitness += (xsegment[i].e - xsegment[i].s);
	for (i = 0; i<yt; i++)
		fitness += (ysegment[i].e - ysegment[i].s);
	for (i = 0; i<rxt; i++)
		fitness += (r_x[i].e - r_x[i].s);
	for (i = 0; i<ryt; i++)
		fitness += (r_y[i].e - r_y[i].s);
	//	printf("%lf\n",fitness);
	//printf("fitness=%lf\n", fitness);
	return fitness;
	
}