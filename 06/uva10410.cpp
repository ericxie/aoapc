#include <cstdio>
#include <list>

const int N=1011;
int d[N],p[N],bfs[N],dfs[N];
std::list<int> G[N];

int main(){
	int i,n,u,v;
	while(~scanf("%d",&n)){
		for(i=1;i<=n;i++){
			scanf("%d",bfs+i);
			d[bfs[i]] = i;
			p[bfs[i]] = 0;
			G[bfs[i]].clear();
		} 
		for(i=1;i<=n;i++) scanf("%d",dfs+i);
		p[dfs[2]] = dfs[1];
		G[dfs[1]].push_back(dfs[2]);
		for(i=3;i<=n;i++){
			u = dfs[i-1];
			v = dfs[i];
			while(d[v] < d[u]) u = p[u];
			if(d[v] == d[u] + 1) p[v] = p[u], G[p[v]].push_back(v);
			else p[v] = u , G[u].push_back(v);
		}
		for(i=1;i<=n;i++){
			printf("%d:",i);
			for(auto x : G[i]) printf(" %d",x);
			putchar('\n');
		}
	}
	return 0;
}