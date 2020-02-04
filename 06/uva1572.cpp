#include <cstdio>
#include <cstring>
#include <vector>
const int N = 52;

int G[N][N],vis[N];

void add(char *s){
	size_t i,j,slot;
	std::vector<int> slots;
	for(i=0;i<4;i++,s+=2) if(*s != '0'){
		slot = (*s - 'A') << 1;
		slot |= *(s+1) == '-';
		slots.push_back(slot);
	}
	if(slots.size() > 1){
		for(i=0; i < slots.size() - 1; i++) {
			for(j= i+1; j<slots.size(); j++) {
				G[slots[i]^1][slots[j]] = 1;
				G[slots[j]^1][slots[i]] = 1;
			}
		}
	}
}

void read(int n){
	int i;
	char s[11];

	memset(G,0,sizeof(G));	
	for(i=0;i<n;i++){
		scanf("%s",s);
		add(s);
	}	
}

bool dfu(int u){
	vis[u] = 1;
	for(int v=0;v<N;v++) if(G[u][v]){
		if(vis[v] == 1 || (vis[v]==0 && !dfu(v))) return false;
	}
	vis[u] = 2;
	return true;
}

bool dfs(){	
	memset(vis,0,sizeof(vis));
	for(int u = 0; u < N; u++) if(vis[u] == 0){
		if(!dfu(u)) return false;
	}
	return true;
}

int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		read(n);
		puts(dfs()?"bounded":"unbounded");
	}
	return 0;
}
