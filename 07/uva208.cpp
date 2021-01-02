#include <cstdio>
#include <list>
#include <array>

const int N = 22;

std::list<int> G[N];
std::array<int,N> vis;
std::list<int> path;
int T,cnt;

void dfs(int u){	
	//fprintf(stderr,"%d\n",u);
	if(u==T){
		cnt++;
		for(auto x : path) printf("%d ",x);
		printf("%d\n",T);
		return;
	}
	vis[u] = 1;
	path.push_back(u);
	for(auto v : G[u]) if(!vis[v]){
		dfs(v);
	}
	path.pop_back();
	vis[u] = 0;
}

bool dfu(int u){
	//fprintf(stderr,"dfu : %d\n",u);
	if(u == T) return true;
	vis[u] = 1;
	for(auto v :G[u]) if(!vis[v]) if(dfu(v)) return true;
	return false;
}

bool read(){
	if(scanf("%d",&T)==EOF) return false;
	for(int i=0;i<N;i++) G[i].clear();
	for(int i=0;i<N;i++) vis[i] = 0;
	path.clear();
	cnt = 0;
	int u,v;
	while(scanf("%d %d",&u,&v),u||v){
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=0;i<N;i++) G[i].sort();
	return true;
}

int main(){
	int k = 0;
	while(read()){
		printf("CASE %d:\n",++k);
		if(!dfu(1)) printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,T);
		else {
			for(int i=0;i<N;i++) vis[i] = 0;
			dfs(1);
			printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,T);
		}
	}
	return 0;
}