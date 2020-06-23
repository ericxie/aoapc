#include <cstdio>
#include <vector>
#include <algorithm>
#define N 10011
const int inf = 1e6;
/*
 * s0 : 父0，自0，唯一子1； s1： 自1； s2：父1，自0，子0
 * u.s1 = sum min(v.s0,v.s1) + 1
 * u.s2 = sum v.s0
 * u.s0 = u.s2 + min{v.s1 - v.s0}
 */
struct node{
	int s[3]; 	  
	int tag;	
	std::vector<int> edge;
	void clear(){
		s[0] = inf, s[1] = 1, s[2] = 0;
		tag = 0;
		edge.clear();
	}
	node(){
		clear();	
	}
	inline void addEdge(int v){
		edge.push_back(v);
	}
}graph[N];

void dfs(int x){
	auto &u = graph[x];
	u.tag = 1;
	int delta = inf;	
	for(int y : u.edge){
		const auto &v = graph[y];				
		if(v.tag == 0) {			
			dfs(y);
			u.s[1] += std::min(v.s[1],v.s[2]);
			u.s[2] += v.s[0];
			if(u.s[1] > inf) u.s[1] = inf;
			if(u.s[2] > inf) u.s[2] = inf;
			delta = std::min(delta,v.s[1]-v.s[0]);	
		}				
	}
	u.s[0] = u.s[2] + delta;	
	//fprintf(stderr,"%d : %d %d %d\n",x, u.s[0],u.s[1],u.s[2]);
	u.tag = 2;
}

int main(){
	int t,i,n,u,v;
	do{
		scanf("%d",&n);
		for(i=1;i<=n;i++) graph[i].clear();
		for(i=0;i<n-1;i++) {
			scanf("%d %d",&u,&v);
			graph[u].addEdge(v);
			graph[v].addEdge(u);
		}
		dfs(1);
		printf("%d\n",std::min(graph[1].s[0],graph[1].s[1]));
		scanf("%d",&t);
		//fprintf(stderr,"----------------\n");
	}while(t != -1);
	return 0;
}