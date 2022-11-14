struct node1 {
	double pos;
	double s;
	double e;
} xsegment[1010],ysegment[1010],r_x[1010],r_y[1010];
struct node2 {
	double sx;
	double sy;
	double ex;
	double ey;
} x45[1010],x135[1010];
bool cmp1(struct node1 a,struct node1 b) {
	if(a.pos<b.pos) return true;
	else return false;
}
bool cmp2(struct node1 a,struct node1 b) {
	if(a.s<b.s) return true;
	else return false;
}
double GetPL(int source, int pos) {

	int i, k, sp, xt = 0, yt = 0, x45t = 0, x135t = 0, rxt = 0, ryt = 0;
	double x1, x2, y1, y2, fx, fy, pathlength = 0.0, midx, midy;
	int cur, pre;
	double tmp1, tmp2;

	//计算pos上的sink到source上的pl
	cur = pos * 3 - 1;
	pre = pos * 3 - 2;
	//printf("len(%d,%d)  ", min_tree[pre], min_tree[cur]);
	x1 = graph[min_tree[pre]][0]; //起点x
	y1 = graph[min_tree[pre]][1]; //起点y
	x2 = graph[min_tree[cur]][0]; //终点x
	y2 = graph[min_tree[cur]][1]; //终点y
	sp = min_tree[pos * 3]; //连接方式
	fx = fabs(x1 - x2);  //水平距离
	fy = fabs(y1 - y2);  //垂直距离
	if (sp == 0 || sp == 1) {
		tmp1 = (sqrt(2) - 1)*(MIN(fx, fy));
		tmp2 = (MAX(fx, fy));
		pathlength += tmp1 + tmp2;
	} else
		pathlength += fx + fy;

	//自底向上
	int pt;
	int flag = 0; //找完路径
	for(pt = pos - 1; pt>=1; pt--) {
		if (min_tree[pre] == source) {
			flag = 1;
			break;
		}
		if (min_tree[pre] == min_tree[pt * 3 - 1]) {
			cur = pt * 3 - 1;
			pre = pt * 3 - 2;
			//printf("len(%d,%d) ", min_tree[pre], min_tree[cur]);
			//计算(pre,cur)的长度
			x1 = graph[min_tree[pre]][0]; //起点x
			y1 = graph[min_tree[pre]][1]; //起点y
			x2 = graph[min_tree[cur]][0]; //终点x
			y2 = graph[min_tree[cur]][1]; //终点y
			sp = min_tree[pt * 3]; //连接方式
			fx = fabs(x1 - x2);  //水平距离
			fy = fabs(y1 - y2);  //垂直距离

			if (sp == 0 || sp == 1) {
				tmp1 = (sqrt(2) - 1)*(MIN(fx, fy));
				tmp2 = (MAX(fx, fy));
				pathlength += tmp1+tmp2;
			} else
				pathlength += fx + fy;

		}

	}

	if (!flag) { //往后寻找
		for (pt = pos + 1; pt <= vertice-1; pt++) {
			if (min_tree[pre] == min_tree[pt * 3 - 1]) {
				cur = pt * 3 - 1;
				pre = pt * 3 - 2;
				//printf("len(%d,%d) ", min_tree[pre], min_tree[cur]);
				//计算(pre,cur)的长度
				x1 = graph[min_tree[pre]][0]; //起点x
				y1 = graph[min_tree[pre]][1]; //起点y
				x2 = graph[min_tree[cur]][0]; //终点x
				y2 = graph[min_tree[cur]][1]; //终点y
				sp = min_tree[pt * 3]; //连接方式
				fx = fabs(x1 - x2);  //水平距离
				fy = fabs(y1 - y2);  //垂直距离

				if (sp == 0 || sp == 1) {
					tmp1 = (sqrt(2) - 1)*(MIN(fx, fy));
					tmp2 = (MAX(fx, fy));
					pathlength += tmp1 + tmp2;
				} else
					pathlength += fx + fy;
			}
			if (min_tree[pre] == source) {
				flag = 1;
				break;
			}
		}
	}
	return pathlength;
}

//获取粒子的PL
double GetMaxPL() {
	int source = gbest.source;
	double maxPL = 0, pl = 0;
	for (int i = 1; i < vertice; i++) {
		pl = GetPL(source, i);
		//	printf("%lf\n", pl);
		if (pl > maxPL)
			maxPL = pl;
	}

	return maxPL;
}

double Getfitness() {
	int i,k,sp,xt=0,yt=0,x45t=0,x135t=0,rxt=0,ryt=0;
	double x1,x2,y1,y2,fx,fy,fitness=0,midx,midy;
	int count;
//	printf("%d\n",vertice);
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",min_tree[i]);
//	printf("\n");
	count=1;
	for(i=1; i<vertice; i++) {
		x1=graph[min_tree[i*3-2]][0];
		y1=graph[min_tree[i*3-2]][1];
		x2=graph[min_tree[i*3-1]][0];
		y2=graph[min_tree[i*3-1]][1];
		sp=min_tree[i*3];
		fx=fabs(x1-x2);
		fy=fabs(y1-y2);
//		count=count+(records1[min_tree[i*3-2]][min_tree[i*3-1]].c[sp]);
		if(records1[min_tree[i*3-2]][min_tree[i*3-1]].c[sp]) count++;
//		printf("%lf %lf %lf %lf %d %lf %lf\n",x1,y1,x2,y2,sp,fx,fy);
		if(sp==2||sp==3) {
			if(sp==2) {
				xsegment[xt].pos=y2;
				ysegment[yt].pos=x1;
			} else {
				xsegment[xt].pos=y1;
				ysegment[yt].pos=x2;
			}
			if(x1>x2) {
				xsegment[xt].s=x2;
				xsegment[xt++].e=x1;
			} else {
				xsegment[xt].s=x1;
				xsegment[xt++].e=x2;
			}
			if(y1>y2) {
				ysegment[yt].s=y2;
				ysegment[yt++].e=y1;
			} else {
				ysegment[yt].s=y1;
				ysegment[yt++].e=y2;
			}
		}
		if(sp==0||sp==1) {
			if(fx==0||fy==0) {
				if(sp==0) {
					xsegment[xt].pos=y1;
					ysegment[yt].pos=x1;
				} else {
					xsegment[xt].pos=y2;
					ysegment[yt].pos=x2;
				}
				if(x1>x2) {
					xsegment[xt].s=x2;
					xsegment[xt++].e=x1;
				} else {
					xsegment[xt].s=x1;
					xsegment[xt++].e=x2;
				}
				if(y1>y2) {
					ysegment[yt].s=y2;
					ysegment[yt++].e=y1;
				} else {
					ysegment[yt].s=y1;
					ysegment[yt++].e=y2;
				}
			} else {
				if(x1>x2) {
					midx=x1;
					midy=y1;
					x1=x2;
					y1=y2;
					x2=midx;
					y2=midy;
					sp=!sp;
				}
				if(fx>fy) {
					if(sp==0) {
						xsegment[xt].pos=y1;
						xsegment[xt].s=x1;
						xsegment[xt++].e=x2-fy;
						if(y1<y2) {
							x45[x45t].sx=x2-fy;
							x45[x45t].sy=y1;
							x45[x45t].ex=x2;
							x45[x45t++].ey=y2;
						} else {
							x135[x135t].sx=x2-fy;
							x135[x135t].sy=y1;
							x135[x135t].ex=x2;
							x135[x135t++].ey=y2;
						}
					} else {
						xsegment[xt].pos=y2;
						xsegment[xt].s=x1+fy;
						xsegment[xt++].e=x2;
						if(y1<y2) {
							x45[x45t].sx=x1;
							x45[x45t].sy=y1;
							x45[x45t].ex=x1+fy;
							x45[x45t++].ey=y2;
						} else {
							x135[x135t].sx=x1;
							x135[x135t].sy=y1;
							x135[x135t].ex=x1+fy;
							x135[x135t++].ey=y2;
						}
					}
				} else {
					if(sp==0) {
						ysegment[yt].pos=x1;
						if(y1<y2) {
							x45[x45t].sx=x1;
							x45[x45t].sy=y2-fx;
							x45[x45t].ex=x2;
							x45[x45t++].ey=y2;
							ysegment[yt].s=y1;
							ysegment[yt++].e=y2-fx;
						} else {
							x135[x135t].sx=x1;
							x135[x135t].sy=y2+fx;
							x135[x135t].ex=x2;
							x135[x135t++].ey=y2;
							ysegment[yt].s=y1;
							ysegment[yt++].e=y2+fx;
						}
					} else {
						ysegment[yt].pos=x2;
						if(y1<y2) {
							x45[x45t].sx=x1;
							x45[x45t].sy=y1;
							x45[x45t].ex=x2;
							x45[x45t++].ey=y1+fx;
							ysegment[yt].s=y1+fx;
							ysegment[yt++].e=y2;
						} else {
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
	for(i=0; i<xt; i++) {
		if(xsegment[i].s>xsegment[i].e) {
			midx=xsegment[i].s;
			xsegment[i].s=xsegment[i].e;
			xsegment[i].e=midx;
		}
	}
	for(i=0; i<yt; i++) {
		if(ysegment[i].s>ysegment[i].e) {
			midy=ysegment[i].s;
			ysegment[i].s=ysegment[i].e;
			ysegment[i].e=midy;
		}
	}
	for(i=0; i<x45t; i++) {
		if(x45[i].sx>x45[i].ex) {
			midx=x45[i].sx;
			midy=x45[i].sy;
			x45[i].sx=x45[i].ex;
			x45[i].sy=x45[i].ey;
			x45[i].ex=midx;
			x45[i].ey=midy;
		}
	}
	for(i=0; i<x135t; i++) {
		if(x135[i].sx>x135[i].ex) {
			midx=x135[i].sx;
			midy=x135[i].sy;
			x135[i].sx=x135[i].ex;
			x135[i].sy=x135[i].ey;
			x135[i].ex=midx;
			x135[i].ey=midy;
		}
	}
	for(i=0; i<x45t; i++) {
		r_x[rxt].pos=P*(x45[i].sy-x45[i].sx);
		r_x[rxt].s=P*(x45[i].sx+x45[i].sy);
		r_x[rxt++].e=P*(x45[i].ex+x45[i].ey);
	}
	for(i=0; i<x135t; i++) {
		r_y[ryt].pos=P*(x135[i].sx+x135[i].sy);
		r_y[ryt].s=P*(x135[i].sy-x135[i].sx);
		r_y[ryt++].e=P*(x135[i].ey-x135[i].ex);
	}

	for(i=0; i<rxt; i++) {
		if(r_x[i].s>r_x[i].e) {
			midx=r_x[i].s;
			r_x[i].s=r_x[i].e;
			r_x[i].e=midx;
		}
	}
	for(i=0; i<ryt; i++) {
		if(r_y[i].s>r_y[i].e) {
			midx=r_y[i].s;
			r_y[i].s=r_y[i].e;
			r_y[i].e=midx;
		}
	}
	sort(xsegment,xsegment+xt,cmp1);
	sort(ysegment,ysegment+yt,cmp1);
	sort(r_x,r_x+rxt,cmp1);
	sort(r_y,r_y+ryt,cmp1);
	for(i=1; i<xt; i++) {
		k=i-1;
		while(i<xt&&xsegment[i].pos==xsegment[i-1].pos)
			i++;
		sort(xsegment+k,xsegment+i,cmp2);
	}
	for(i=1; i<yt; i++) {
		k=i-1;
		while(i<yt&&ysegment[i].pos==ysegment[i-1].pos)
			i++;
		sort(ysegment+k,ysegment+i,cmp2);
	}
	for(i=1; i<rxt; i++) {
		k=i-1;
		while(i<rxt&&r_x[i].pos==r_x[i-1].pos)
			i++;
		sort(r_x+k,r_x+i,cmp2);
	}
	for(i=1; i<ryt; i++) {
		k=i-1;
		while(i<ryt&&r_y[i].pos==r_y[i-1].pos)
			i++;
		sort(r_y+k,r_y+i,cmp2);
	}
	for(i=1; i<xt; i++) {
		if(xsegment[i].pos==xsegment[i-1].pos)
			if(xsegment[i].s==xsegment[i-1].s) {
				if(xsegment[i].e<xsegment[i-1].e)
					xsegment[i].e=xsegment[i-1].e;
				xsegment[i-1].pos=0;
				xsegment[i-1].s=0;
				xsegment[i-1].e=0;
			} else {
				if(xsegment[i].s<xsegment[i-1].e) {
					xsegment[i].s=xsegment[i-1].s;
					if(xsegment[i].e<xsegment[i-1].e)
						xsegment[i].e=xsegment[i-1].e;
					xsegment[i-1].pos=0;
					xsegment[i-1].s=0;
					xsegment[i-1].e=0;
				}
			}
	}
	for(i=1; i<yt; i++) {
		if(ysegment[i].pos==ysegment[i-1].pos)
			if(ysegment[i].s==ysegment[i-1].s) {
				if(ysegment[i].e<ysegment[i-1].e)
					ysegment[i].e=ysegment[i-1].e;
				ysegment[i-1].pos=0;
				ysegment[i-1].s=0;
				ysegment[i-1].e=0;
			} else {
				if(ysegment[i].s<ysegment[i-1].e) {
					ysegment[i].s=ysegment[i-1].s;
					if(ysegment[i].e<ysegment[i-1].e)
						ysegment[i].e=ysegment[i-1].e;
					ysegment[i-1].pos=0;
					ysegment[i-1].s=0;
					ysegment[i-1].e=0;
				}
			}
	}
	for(i=1; i<rxt; i++) {
		if(r_x[i].pos==r_x[i-1].pos)
			if(r_x[i].s==r_x[i-1].s) {
				if(r_x[i].e<r_x[i-1].e)
					r_x[i].e=r_x[i-1].e;
				r_x[i-1].pos=0;
				r_x[i-1].s=0;
				r_x[i-1].e=0;
			} else {
				if(r_x[i].s<r_x[i-1].e) {
					r_x[i].s=r_x[i-1].s;
					if(r_x[i].e<r_x[i-1].e)
						r_x[i].e=r_x[i-1].e;
					r_x[i-1].pos=0;
					r_x[i-1].s=0;
					r_x[i-1].e=0;
				}
			}
	}
	for(i=1; i<ryt; i++) {
		if(r_y[i].pos==r_y[i-1].pos)
			if(r_y[i].s==r_y[i-1].s) {
				if(r_y[i].e<r_y[i-1].e)
					r_y[i].e=r_y[i-1].e;
				r_y[i-1].pos=0;
				r_y[i-1].s=0;
				r_y[i-1].e=0;
			} else {
				if(r_y[i].s<r_y[i-1].e) {
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
	for(i=0; i<xt; i++)
		fitness+=(xsegment[i].e-xsegment[i].s);
	for(i=0; i<yt; i++)
		fitness+=(ysegment[i].e-ysegment[i].s);
	for(i=0; i<rxt; i++)
		fitness+=(r_x[i].e-r_x[i].s);
	for(i=0; i<ryt; i++)
		fitness+=(r_y[i].e-r_y[i].s);
	if(count>1)sign=1;
//	printf("%d\n",count);
//	fitness*=count;
	fitness=fitness+(count-1)*0.01*fitness;
//	printf("%lf %d\n",fitness,count);
	return fitness;
}
