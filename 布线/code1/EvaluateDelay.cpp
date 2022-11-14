bool decmp(struct pinslack a,struct pinslack b) {
	if(a.AAT>=b.AAT)
		return true;
	else
		return false ;
}
int index=0;
//找到叶节点
void FindLeaves() {
	leaves.clear();
	set<int> visited;
	int i;
//	map<int, int>::iterator it = leaves.begin();

//	leaves.insert(pair<int, int>(min_tree[1], 0));
	for (i = 1; i <= vertice - 1; i++) {
		if ((leaves.find(min_tree[i * 3 - 2])) == leaves.end()&&visited.find(min_tree[i * 3 - 2])==visited.end()) {
			leaves.insert(pair<int, int>(min_tree[i * 3 - 2], i));
			visited.insert(min_tree[i * 3 - 2]);
		} else if((leaves.find(min_tree[i * 3 - 2])) != leaves.end()&&visited.find(min_tree[i * 3 - 2])!=visited.end()) {
			leaves.erase(min_tree[i * 3 - 2]);
		}
		if ((leaves.find(min_tree[i * 3 - 1])) == leaves.end()&&visited.find(min_tree[i * 3 - 1])==visited.end()) {
			leaves.insert(pair<int, int>(min_tree[i * 3 - 1], i));
			visited.insert(min_tree[i * 3 - 1]);
		} else if((leaves.find(min_tree[i * 3 - 1])) != leaves.end()&&visited.find(min_tree[i * 3 - 1])!=visited.end()) {
			leaves.erase(min_tree[i * 3 - 1]);
		}
	}

//	for (map<int, int>::iterator it = leaves.begin(); it != leaves.end(); it++)
//		printf("(%d, %d) ", it->first,it->second);
//	printf("\nparticle: ");
//	for (i = 1; i <= 3 * (vertice - 1); i++)
//		printf("%d ", min_tree[i]);
//	printf("\n");
}

//计算每个点所在的下游电容
void CalDownstreamCap() {
	int i, sp;
	double tmp1, tmp2;
	double x1, x2, y1, y2, fx, fy, pathlen = 0;
	DownCaps.clear();
	map<int, double>::iterator it =  DownCaps.begin();

	for(i = 1; i <= vertice; i++)
		DownCaps.insert(pair<int, double>(i, C_sink));

	double downstream = 0;
	for (i = vertice - 1; i >=1; i--) {
//		cout<<"1111"<<min_tree[i * 3 - 2]<<" "<<min_tree[i * 3 - 1]<<endl;
		x1 = graph[min_tree[i * 3 - 2]][0]; //起点x
		y1 = graph[min_tree[i * 3 - 2]][1]; //起点y
		x2 = graph[min_tree[i * 3 - 1]][0]; //终点x
		y2 = graph[min_tree[i * 3 - 1]][1]; //终点y
		sp = min_tree[i * 3]; //连接方式
		fx = fabs(x1 - x2);  //水平距离
		fy = fabs(y1 - y2);  //垂直距离
		if (sp == 0 || sp == 1) {
			tmp1 = (sqrt(2) - 1)*(MIN(fx, fy));
			tmp2 = (MAX(fx, fy));
			pathlen = tmp1 + tmp2;
		} else
			pathlen = fx + fy;

		DownCaps[min_tree[i * 3 - 2]] += pathlen*c_0 + DownCaps[min_tree[i * 3 - 1]];
//		cout<<"DownCaps"<<min_tree[i * 3 - 2]<<" = "<<DownCaps[min_tree[i * 3 - 2]]<<endl;
	}
}

//计算某个pos的时延
double CalculateSTDelay(int pos) {
	double x1, x2, y1, y2, fx, fy, dis = 0;
	double C_down = 0, delay = 0;
	double tmp1, tmp2;
	int sp, cur, pre, source;

	//找到pos到source之间的路径
	source = 1;
	cur = pos * 3 - 1;
	pre = pos * 3 - 2;
//	printf("len(%d,%d)  ", min_tree[pre], min_tree[cur]);
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
		dis = tmp1 + tmp2;
	} else
		dis = fx + fy;

	delay += dis*r_0*(dis*c_0 / 2 + DownCaps[min_tree[cur]]);

	//自底向上
	int pt;
	int flag = 0; //找完路径
	for (pt = pos - 1; pt >= 1; pt--) {
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
				dis = tmp1 + tmp2;
			} else
				dis = fx + fy;

			delay += dis*r_0*(dis*c_0 / 2 + DownCaps[min_tree[cur]]);
		}
	}

	if (!flag) { //往后寻找
		for (pt = pos + 1; pt <= vertice - 1; pt++) {
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
					dis = tmp1 + tmp2;
				} else
					dis = fx + fy;

				delay += dis*r_0*(dis*c_0 / 2 + DownCaps[min_tree[cur]]);
			}
			if (min_tree[pre] == source) {
				flag = 1;
				break;
			}
		}
	}

//	printf("delay(%d--%d): %lf\n", source, min_tree[pos * 3 - 1], delay);
	return delay;
}

int ver;
double EvaluteRAT() {
	ver=vertice;
	int i;
	int source = 1;
	double RAT,tmp,k;
	queue<int> q1,q2;
	for (i = 1; i <= (vertice-1) ; i++) {
		min_tree[i * 3 - 2] = gbest.edge[i * 3 - 2];
		min_tree[i * 3 - 1] = gbest.edge[i * 3 - 1];
		min_tree[i * 3] = gbest.edge[i * 3];
//		cout<<min_tree[i * 3 - 2]<<" "<<min_tree[i*3-1]<<endl;
	}
	for (i = 1; i <= (vertice - 1); i++) {
		mtree[min_tree[i * 3 - 2]].push_back(min_tree[i * 3 - 1]);
		mtree[min_tree[i * 3 - 1]].push_back(min_tree[i * 3 - 2]);
	}
	CalDownstreamCap();
	FindLeaves();

	set<int> visited1;
	visited1.insert(source);
	pinslack[source].AAT=0;
	while(1) {
		for(i = 1; i < vertice; i++) {
//			cout<<"111 "<<pin2edge[min_tree[i * 3 - 1]]<<","<<"222 "<<pin2edge[min_tree[i * 3 - 2]]<<endl;
			if((visited1.find(min_tree[i * 3 - 1])!=visited1.end())&&(visited1.find(min_tree[i * 3 - 2])!=visited1.end())) continue;

			if(visited1.find(min_tree[i * 3 - 2])!=visited1.end()) { //点pre在已访问节点集合中
				visited1.insert(min_tree[i * 3 - 1]);
				pinslack[min_tree[i * 3 - 1]].AAT = pinslack[min_tree[i * 3 - 2]].AAT+ (CalculateSTDelay(pin2edge[min_tree[i * 3 - 1]])-CalculateSTDelay(pin2edge[min_tree[i * 3 - 2]]));

			}

		}
//		cout<<"size "<<visited1.size()<<endl;
		if(visited1.size()==vertice) break;
	}
	k=pinslack[1].AAT;
	for(i = 2; i <= vertice; i++) {
		if(k<pinslack[i].AAT) {
			k=pinslack[i].AAT;
		}
	}
//	sort(pinslack+1,pinslack+vertice+1,decmp);
//	k=(int)(vertice*0.15);
//	k=pinslack[1].AAT;
	cout<<"k= "<<k<<endl;

	for(auto & leave:leaves) {
		ratvalue.insert(pair<int, double>(leave.first, k-820000));
	}

	q1.push(source);
	father[source]=0;
	while (!q1.empty()) {
		int pos=q1.front();
		q1.pop();
		vector<int> neighbors=mtree[pos];
		for(auto & neighbor:neighbors) {
			if(father.find(pos)!=father.end()&&neighbor==father[pos]) continue;
			father[neighbor]=pos;
			q1.push(neighbor);
		}
	}
//	for(auto &f:father) {
//		cout<<"father:"<<f.first<<" "<<f.second<<endl;
//	}
	for(auto &leave:leaves) {
		int cur=leave.first;
		while(1) {
			int next=father[cur];
			if(next==0) break;
			if(ratvalue.find(next)!=ratvalue.end()) { //有值
				ratvalue[next]=ratvalue[next]<ratvalue[cur]-(CalculateSTDelay(pin2edge[cur])-CalculateSTDelay(pin2edge[next]))?ratvalue[next]:ratvalue[cur]-(CalculateSTDelay(pin2edge[cur])-CalculateSTDelay(pin2edge[next]));
			} else { //无值
				ratvalue[next]=ratvalue[cur]-(CalculateSTDelay(pin2edge[cur])-CalculateSTDelay(pin2edge[next]));

			}
			//cout<<"tttt"<<CalculateSTDelay(pin2edge[cur])-CalculateSTDelay(pin2edge[next])<<endl;
			cur=next;
		}
	}
//	for(auto& rat:ratvalue) {
//		cout<<"Rat "<<rat.first<<" "<<rat.second<<endl;
//	}

	int count=0;
	for(i = 1; i <= vertice; i++) {
		pinslack[i].slack=ratvalue[i]-pinslack[i].AAT;
//		cout<<"i= "<<i<<" Aat= "<<pinslack[i].AAT<<endl;
//		cout<<"i= "<<i<<" Slack= "<<pinslack[i].slack<<endl;
		if(pinslack[i].slack<0) count++;
	}
	double ratio;
	ratio = (count*1.0/vertice)*100;
	cout<<"count = "<<count<<endl;
	cout<<"ratio = "<<ratio<<"%"<<endl;

}

double EvaluteSlack() {
	int i;
	double tmp,wns;
	for (i = 1; i <= (vertice-1); i++) {
		min_tree[i * 3 - 2] = gbest.edge[i * 3 - 2];
		min_tree[i * 3 - 1] = gbest.edge[i * 3 - 1];
		min_tree[i * 3] = gbest.edge[i * 3];
//		cout<<min_tree[i * 3 - 2]<<" "<<min_tree[i*3-1]<<endl;
	}

	CalDownstreamCap();

	int source = 1;
	set<int> visited1;
	visited1.insert(source);
	pinslack[source].AAT=0;
	while(1) {
		for(i = 1; i < vertice; i++) {
//			cout<<"333 "<<pin2edge[min_tree[i * 3 - 1]]<<","<<"444 "<<pin2edge[min_tree[i * 3 - 2]]<<endl;
			if((visited1.find(min_tree[i * 3 - 1])!=visited1.end())&&(visited1.find(min_tree[i * 3 - 2])!=visited1.end())) continue;

			if(visited1.find(min_tree[i * 3 - 2])!=visited1.end()) { //点pre在已访问节点集合中
				visited1.insert(min_tree[i * 3 - 1]);
				pinslack[min_tree[i * 3 - 1]].AAT = pinslack[min_tree[i * 3 - 2]].AAT+ (CalculateSTDelay(pin2edge[min_tree[i * 3 - 1]])-CalculateSTDelay(pin2edge[min_tree[i * 3 - 2]]));
			}
			if(visited1.find(min_tree[i * 3 - 1])!=visited1.end()) { //点pre在已访问节点集合中
				visited1.insert(min_tree[i * 3 - 2]);
				pinslack[min_tree[i * 3 - 2]].AAT = pinslack[min_tree[i * 3 - 1]].AAT+ (CalculateSTDelay(pin2edge[min_tree[i * 3 - 2]])-CalculateSTDelay(pin2edge[min_tree[i * 3 - 1]]));
			}
		}
		//cout<<"size "<<visited1.size()<<endl;
		if(visited1.size()==vertice) break;
	}
//	for(auto& rat:ratvalue) {
//		cout<<"rat "<<rat.first<<" "<<rat.second<<endl;
//	}
	int co=0;
	for(i = 1; i <= ver; i++) {
		pinslack[i].slack=ratvalue[i]-pinslack[i].AAT;
//		cout<<"i= "<<i<<" aat= "<<pinslack[i].AAT<<endl;
//		cout<<"i= "<<i<<" slack= "<<pinslack[i].slack<<endl;
		if(pinslack[i].slack<0) co++;
	}
	double ra;
	ra = (co*1.0/vertice)*100;
	cout<<"co= "<<co<<endl;
	cout<<"ra = "<<ra<<"%"<<endl;
	wns=INT_MAX;
	for(i=2; i <= ver; i++) {
		if(wns>pinslack[i].slack) {
			wns=pinslack[i].slack;
		}
	}
	return wns;
}

