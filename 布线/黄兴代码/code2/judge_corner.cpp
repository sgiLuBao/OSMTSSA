void  judge_corner(int curt)
{
	int p1,p2,c1,c2;
	int i1,i2;
	double length=0,le=0;
	int pp1,pp2,i3;
    bool flag=false;
	p1=terminal[curt].edge_pos[0]; 
	p2=terminal[curt].edge_pos[1];
	if(edge[p1].s>ini_v_num||edge[p2].e>ini_v_num) flag=true;
	c1=edge[p1].c;
	c2=edge[p2].c;
	i1=edge[p1].index;
	i2=edge[p2].index;
	pp1=edge[p1].s;
	pp2=edge[p2].e;
	i3=del_index[pp1][pp2];	
	if((records1[i3].c[2]==0||records1[i3].c[3]==0)&&!flag)
	{
	 length=(records2[i1][c1].eh-records2[i1][c1].sh)+(records2[i1][c1].ev-records2[i1][c1].sv)+(records2[i1][c1].e45-records2[i1][c1].s45)+(records2[i1][c1].e135-records2[i1][c1].s135)+(records2[i2][c2].eh-records2[i2][c2].sh)+(records2[i2][c2].ev-records2[i2][c2].sv)+(records2[i2][c2].e45-records2[i2][c2].s45)+(records2[i2][c2].e135-records2[i2][c2].s135);
	 if(records1[i3].c[2]==0)
	 le=(records2[i3][2].eh-records2[i3][2].sh)+(records2[i3][2].ev-records2[i3][2].sv);
	 else 
	 le=(records2[i3][3].eh-records2[i3][3].sh)+(records2[i3][3].ev-records2[i3][3].sv);
	 if(length>le||length-le<1e-6)
	 {		 
//	 	printf("%d:\n",curt);
//		printf("%d %d %d,%d %d %d»»³É%d %d\n",edge[p1].s,edge[p1].e,edge[p1].c,edge[p2].s,edge[p2].e,edge[p2].c,pp1,pp2);
		 graph[curt][2]=0;
		 edge[p1].e=pp2;
		 if(records1[i3].c[2]==0) edge[p1].c=2;
		 else edge[p1].c=3;
		 edge[p1].index=i3;
		 edge[p1].mark=true;
		 edge[p2].mark=false;
		 dc++;
	 }
	}
}