#include <vector>
#include <cstdio>
const int N = 1011;
std::vector<int> G[N];
int vis[N];

void read(int n,int m){
	int i,a,b;

	for(i=1;i<=n;i++) G[i].clear(),vis[i]=3;
	for(i=0;i<m;i++){
		scanf("%d %d",&a,&b);
		vis[a] = vis[b] = 0;
		G[a].push_back(b);
		G[b].push_back(a);
	}
}

int dfs(int u){
	int res = G[u].size() & 1;
	vis[u] = 1;
	for(auto v : G[u]){
		if(vis[v] == 0) res += dfs(v);
	}
	vis[u] = 2;	
	return res;
}

int dfu(int n){
	int res = 0,k = 0,t;
	for(int i = 1; i <= n; i++) if(vis[i] == 0) {
			t = 0;
			res++;			
			t += dfs(i);
			if(t > 2) k += (t - 2) >> 1;		
	}	
	return (res < 2 ? 0 : res - 1) + k;
}

int main(){
	int n,m,t,k=0;
	while(scanf("%d %d %d",&n,&m,&t),n!=0){
		read(n,m);
		printf("Case %d: %d\n",++k, (dfu(n) + m) * t);
	}
	return 0;
}

