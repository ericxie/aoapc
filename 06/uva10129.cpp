#include <cstdio>
#include <vector>
#include <cstring>

const int N = 26;

struct Graph{
	int degree[N];
	std::vector<int> G[N];
	int vis[N];
	bool isEularPath(){
		int din=0,dout=0;
		for(int i = 0; i < N && din< 2 && dout < 2; i++){
			if(degree[i] == -1) din++;
			else if(degree[i] == 1) dout++;
			else if(degree[i] >= 2 || degree[i] <= -2) return false; 
		}
		return din + dout <= 2;
	}
	int dfs(int u){
		int cnt = 1;
		vis[u] = 1;
		for(auto v : G[u]) if(!vis[v]) cnt += dfs(v);
		return cnt; 
	}

	bool isConnect(){
		memset(vis,0,sizeof(vis));	
		int n=0;
		for(int i = 0; i < N; i++) if(!G[i].empty()) n++;	
		for(int i = 0; i < N; i++) if(!vis[i] && !G[i].empty()){
			return dfs(i) == n;
		}
		return false;
	}

	Graph(){ 
		memset(degree,0,sizeof(degree));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<N;i++) G[i].clear();
	}

	void read(){
		int n,u,v;
		char buf[1111];
		scanf("%d",&n);
		while(n--){
			scanf("%s",buf);
			u = buf[0] - 'a';
			v = buf[strlen(buf) - 1] - 'a';
			degree[u]--;
			degree[v]++;
			G[u].push_back(v);
			G[v].push_back(u);
		}
	}
};

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		Graph a;
		a.read();
		puts(a.isEularPath() && a.isConnect() ? "Ordering is possible.": "The door cannot be opened.");
	}
	return 0;
}