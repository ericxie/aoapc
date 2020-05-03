#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>


#define N 100011

std::vector<std::pair<int,int> > G[N];
int step[N];

void readEdge(size_t n,size_t m){
	for(size_t i=1;i<=n;i++) G[i].clear();
	int u,v,c;
	for(size_t i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&c);
		if(u != v){
			G[u].emplace_back(v,c);
			G[v].emplace_back(u,c);+
		}
	}
}

void bfs1(int n,int sid){
	std::queue<int> Q;
	memset(step,0x3f,sizeof(int)*(n+1));
	
	Q.push(sid);
	step[sid] = 0;	
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(auto &x : G[u]){
			int v = x.first;
			if(step[v] > step[u] + 1){
				step[v] = step[u] + 1;
				Q.push(v); 
			} 			
		}
	}
}

int getMinColor(const std::vector<int> &nodes,int level){
	int ret = 2e9;
	for(int u : nodes){
		for(auto x : G[u]){
			int v = x.first;
			int c = x.second;
			if(step[v] == level && c < ret) ret = c;
		}
	}
	return ret;
}

void nextLevel(const std::vector<int> &cur,std::vector<int> &next,int level,int minColor){
	next.clear();
	for(int u : cur){
		for(auto x : G[u]){
			int v = x.first;
			int c = x.second;
			if(step[v] == level && c == minColor) next.push_back(v);
		}
	}
	std::sort(next.begin(),next.end());
	auto last = std::unique(next.begin(),next.end());
	next.erase(last,next.end());
}

std::vector<int> color;

void bfs2(int sid){
	std::vector<int> nodes[2];
	nodes[0].push_back(sid);
	int level = step[sid];
	int k = 0;
	color.clear();
	while(level){

		int minColor = getMinColor(nodes[k&1],level-1);
		color.push_back(minColor);
		nextLevel(nodes[k&1],nodes[~k&1],level-1,minColor);
		k++;
		level--;
	}
}

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		readEdge(n,m);
		bfs1(n,n);
		bfs2(1);
		int k = color.size();
		printf("%d\n",k);
		for(int i=0;i<k;i++) printf("%d%c",color[i]," \n"[i==k-1]);
	}
	return 0;
}