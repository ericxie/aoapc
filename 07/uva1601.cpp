#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 256;
std::vector<int> G[N];

inline int encode(int *a,int sz){ 
	int id = 0;
	for(int i = 0; i < sz; i++){
		id <<= 8;
		id |= a[i];
	}
	return id;
}

inline void decode(int id,int *a,int sz){
	for(int i = sz - 1; i >= 0; i--){
		a[i] = id & 0xff;
		id >>= 8;
	}
}

int p2xy[N][2];
int xy2p[18][18];
int dist[N*N*N];
char house[18][18];
int start[3],end[3];
int cnt;

void readGraph(int n,int m){
	int i,j,x,y,dx[5]={0,0,1,-1,0},dy[5]={1,-1,0,0,0};
	
	getchar();
	for(j=0;j<=m+1;j++) house[0][j] = house[n+1][j] = '#';
	for(i=1;i<=n;i++){
		house[i][0] = '#';
		for(j=1;j<=m;j++) house[i][j] = getchar();
		getchar();
		house[i][m+1] = '#';
	}
	
	cnt = 1;
	memset(start,0,sizeof(start));
	memset(end,0,sizeof(end));
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(house[i][j] != '#'){
		p2xy[cnt][0] = i;
		p2xy[cnt][1] = j;
		xy2p[i][j] = cnt;
		if(house[i][j]>='A' && house[i][j]<='C') end[house[i][j] - 'A'] = cnt;
		else if (house[i][j]>='a' && house[i][j]<='c') start[house[i][j] - 'a'] = cnt;
		cnt++;
	}
	for(i=1;i<cnt;i++) {
		x = p2xy[i][0];
		y = p2xy[i][1];
		G[i].clear();
		for(j=0;j<5;j++) {			
			if(house[x+dx[j]][y+dy[j]] != '#'){
				G[i].push_back(xy2p[x+dx[j]][y+dy[j]]);
			}
		}
	}	
}

bool bfs(int sz){
	std::queue<int> Q;
	memset(dist,-1,sizeof(dist));
	int startID = encode(start,sz);	
	Q.push(startID);
	dist[startID] = 0;
	int endID = encode(end,sz);
	
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		
		int curr[3],next[3];
		decode(u,curr,sz);		
		int v;
		switch(sz){
			case 1: 
				for(auto x : G[curr[0]]){
					next[0] = x;
					v = encode(next,sz);
					if(v == endID) {
						printf("%d\n",dist[v] = dist[u]+1);
						return true;
					}
					if(dist[v] == -1) {
						dist[v] = dist[u] + 1;
						Q.push(v);
					}
				}	
				break;
			case 2:
				for(auto x : G[curr[0]]){
					for(auto y : G[curr[1]]){						
						if(x==curr[1] && y== curr[0]) continue;
						if(x==y) continue;
						
						next[0] = x;
						next[1] = y;
						v = encode(next,sz);
						if(v == endID) {
							printf("%d\n",dist[v] = dist[u]+1);
							return true;
						}
						if(dist[v] ==-1) {
							dist[v] = dist[u] + 1;
							Q.push(v);
						}

					}
				}
				break;
			case 3:
				for(auto x : G[curr[0]]){
					for(auto y : G[curr[1]]){
						for(auto z : G[curr[2]]){
							if( x==curr[1] && y== curr[0] ||
								x==curr[2] && z== curr[0] ||
								y==curr[2] && z== curr[1]
							 ) continue;	
							if(x==y || y==z || x==z) continue;
							next[0] = x;
							next[1] = y;
							next[2] = z;
							v = encode(next,sz);
							if(v == endID) {
								printf("%d\n",dist[v] = dist[u]+1);
								return true;
							}
							if(dist[v] ==-1) {
								dist[v] = dist[u] + 1;
								Q.push(v);
							}
 						}
					}
				}
				break;
		}		
	}
	return false;
}

int main(){
	int n,m,sz;
	
	while(scanf("%d %d %d",&m,&n,&sz),n){		
		readGraph(n,m);
		bfs(sz);
	}
	return 0;
}








