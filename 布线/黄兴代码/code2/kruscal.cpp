double dis(int i,int j) 
{
   double x1=graph[i][0];
   double y1=graph[i][1];
   double x2=graph[j][0];
   double y2=graph[j][1];
   return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
struct length
{
	int s,e;
	double l;
}e[MAX*2];
bool leng(struct length a,struct length b)
{
   return a.l<b.l;
}
int parent[MAX];
void Initial(int n)
{ 
   for(int i=1;i<=n;i++)
     parent[i]=i;
}
int find_set(int x)
{
   int temp;
   if(parent[x]==x)  return x;
   else
   {
    temp=parent[x];
    parent[x]=find_set(temp);
    return parent[x];
   }
}
bool union_set(int a,int b)
{
 int pa=find_set(a);
 int pb=find_set(b);
 if(pa!=pb)
 {
  parent[pb]=pa;
  return true;
 }
 else return false;
}
//int vv[MAX]={0};
void kruscal()
{
    int i,j,k;
    k=1;
//	printf("tri_num:%d\n",tri_num);
	for(i=1;i<=tri_num;i++)
	{
//    vv[triangle[i].a]=1;
//	   vv[triangle[i].b]=1;
//	   vv[triangle[i].c]=1;

	   if(s[triangle[i].a][triangle[i].b]==false)
	   {
          s[triangle[i].a][triangle[i].b]=true;
		  s[triangle[i].b][triangle[i].a]=true;
		  e[k].s=triangle[i].a;
		  e[k].e=triangle[i].b;
		  e[k++].l=dis(triangle[i].a,triangle[i].b);
	   }
	   if(s[triangle[i].a][triangle[i].c]==false)
	   {
          s[triangle[i].a][triangle[i].c]=true;
		  s[triangle[i].c][triangle[i].a]=true;
		  e[k].s=triangle[i].a;
		  e[k].e=triangle[i].c;
		  e[k++].l=dis(triangle[i].a,triangle[i].c);
	   }
	   if(s[triangle[i].b][triangle[i].c]==false)
	   {
          s[triangle[i].b][triangle[i].c]=true;
		  s[triangle[i].c][triangle[i].b]=true;
		  e[k].s=triangle[i].b;
		  e[k].e=triangle[i].c;
		  e[k++].l=dis(triangle[i].b,triangle[i].c);
	   }
	}
 // printf("vertice:%d\n",vertice);
//	printf("剖分三角形总边数：%d\n",k-1);
    Initial(vertice+1);
//	for(i=1;i<=vertice;i++)
//		printf("%d ",vv[i]);
//	printf("\n");
    sort(e+1,e+k,leng);
	j=1;
    for(i=1;i<k;i++)
	{
      if(union_set(e[i].s,e[i].e)) 
	  { 
         edge[j].s=e[i].s;
         edge[j].e=e[i].e;
         edge[j].index=j;
	   j++;
	  }
      if(j==vertice)
      break;
	}

//	printf("生成树边数：=%d\n",j-1);
//   for(i=1;i<vertice;i++)
//        printf("%d %d %d\n",edge[i].s,edge[i].e,edge[i].index);
}