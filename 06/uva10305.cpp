#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>

const int N = 111;
struct Graph{
	std::vector<int> G[N];
	std::stack<int> res;
	int vis[N];
	int V,E;
	Graph(int v,int e):V(v),E(e){
		for(int i=0;i<V;i++) G[i].clear();		
	}
	inline void read(){
		int i,u,v;
		for(i=0;i<E;i++){
			scanf("%d %d",&u,&v);
			G[u-1].push_back(v-1);
		}
	}
	void dfs(int u){
		vis[u] = 1;
		for(auto v : G[u]) if(!vis[v]) dfs(v);
		res.push(u+1);
	}

	void out(){
		int t = 0;
		while(!res.empty()){
			if(t) putchar(' ');
			t = 1;
			printf("%d",res.top());
			res.pop();
		}
		putchar('\n');
	}

	void topo(){
		memset(vis,0,sizeof(vis));
		for(int i = 0; i < V; i++) if(!vis[i])	dfs(i);
		out();
	}

	
};

int main(){
	int n,m;
	while(scanf("%d %d",&n,&m),n||m){
		Graph g(n,m);
		g.read();
		g.topo();
	}
	return 0;
}



