double obs[10010][4];
int is_judge[10010]; 
void strict_barr()
{
	int i,j,k,kk,obs_num;
	int mid,index=4;
	vector < int > ob_mid;	
	double distance[4] = {0};
	obs_num=0;
	for(i=1;i<= barr_num;i++)
	{
	   for(j=0;j<4;j++)
	   obs[i][j]=barr[i][j];
	   is_judge[i]=1;
     }
    cout<<"barr_num="<<barr_num<<endl; 
    for(i=1;i<=barr_num;i++)
	{
	   if(is_judge[i]==0)continue;
	   ob_mid.clear();
	   ob_mid.push_back(i);
	   for(j=i+1;j<=barr_num;j++)
	   {
	   	   if(is_judge[j]==0)continue;
	   	   if(obs[i][0]>obs[j][2]||obs[i][2]<obs[j][0]||obs[i][1]>obs[j][3]||obs[i][3]<obs[j][1])
	   	   continue;
	   	   else
	   	   {
	   	   	is_judge[j]=0;
	   	   	ob_mid.push_back(j);
	   	   	obs[i][0]=obs[i][0]<obs[j][0]?obs[i][0]:obs[j][0];
	   	   	obs[i][1]=obs[i][1]>obs[j][1]?obs[i][1]:obs[j][1];
	   	   	obs[i][2]=obs[i][2]<obs[j][2]?obs[i][2]:obs[j][2];
	   	   	obs[i][3]=obs[i][3]>obs[j][3]?obs[i][3]:obs[j][3];
			  }
	   }
	   for(k=1;k<=vertice;k++)
	   {
	   	if(graph[k][0]<obs[i][2]&&graph[k][0]>obs[i][0]&&graph[k][1]>obs[i][1]&&graph[k][1]<obs[i][3])
	   	{
	   		cout<<"ob_mid.size()="<<ob_mid.size()<<endl;
	   		for(kk=0;kk<ob_mid.size();kk++)
	   		{
	   			if(graph[k][0]<barr[kk][2]&&graph[k][0]>barr[kk][0])
	   			{
	   				if(!(obs[i][1]>=barr[kk][3]||graph[k][1]<=barr[kk][3]))
	   				{
	   					distance[0]=-1;
					   }
					if(!(graph[k][1]>=barr[kk][3]||obs[i][3]<=barr[kk][3]))
	   				{
	   					distance[1]=-1;
					   }
				   }
				if(graph[k][1]<barr[kk][3]&&graph[k][1]>barr[kk][1])
	   			{
	   				if(!(obs[i][0]>=barr[kk][2]||graph[k][0]<=barr[kk][0]))
	   				{
	   					distance[2]=-1;
					   }
					if(!(graph[k][0]>=barr[kk][2]||obs[k][2]<=barr[kk][0]))
	   				{
	   					distance[3]=-1;
					   }
				   }
			   }
			   if(distance[0]!=-1)
			   distance[0]=fabs(obs[i][1]-graph[k][1]); 
			   if(distance[1]!=-1)
			   distance[1]=fabs(obs[i][3]-graph[k][1]);
			   if(distance[2]!=-1)
			   distance[2]=fabs(obs[i][0]-graph[k][0]); 
			   if(distance[3]!=-1)
			   distance[3]=fabs(obs[i][2]-graph[k][0]);
			   mid=INT_MAX;  
			   for(kk=0;kk<4;kk++)
			   {
			   	 if(distance[kk] == -1)  continue;
				  if(mid>distance[kk])
				  {
				  	mid=distance[kk];
				  	index=kk;
				   } 
				} 
				cout<<"distance="<<distance[index]<<endl;
				if(index==0) {	
			        graph[k][1]=obs[i][1];
				}
				else if(index==1)
				{
					graph[k][1]=obs[i][3];
				}
				else if(index==2)
				{
					graph[k][0]=obs[i][0];
				}
				else if(index==3)
				{
					graph[k][0]=obs[i][2];
				}
				else printf("graph点重新选取错误\n");
		   }
	   }
	   barr[++obs_num][0]=obs[i][0];
	   barr[obs_num][1]=obs[i][1];
	   barr[obs_num][2]=obs[i][2];
	   barr[obs_num][3]=obs[i][3];
    }
    barr_num=obs_num;
    cout<<"barr_num="<<barr_num<<endl;
}
