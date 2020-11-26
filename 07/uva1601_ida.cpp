#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

const int N = 256;
const int inf = 0x3f3f3f3f;

std::vector<int> G[N];

inline int encode(int *a,int sz){ 
	int id = 0;
	for(int i = 0; i < sz; i++){
		id <<= 8;
		id |= a[i];
	}
	return id;
}

int p2xy[N][2];
int xy2p[18][18];
int dist[3][N];
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

void dijkstra(int sz,int k,int s){
	std::queue<int> Q;
	memset(dist[k],0x3f,sizeof(dist[k]));
	
	Q.push(s);
	dist[k][s] = 0;
	
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();

		for(auto v : G[u]){
			if(dist[k][u] + 1 < dist[k][v]) {
				dist[k][v] = dist[k][u] + 1;
				Q.push(v);
			}
		}				
	}
}

int ans;

inline int hx(int *curr,int sz){
	int h = 0;
	for(int i = 0; i<sz; i++){
		h = std::max(h,dist[i][curr[i]]);
	} 
	return h;
}

bool dfs(int maxd,int d,int *curr,int sz){
	if(d == maxd){
		if(encode(curr,sz) == encode(end,sz)){
			ans = maxd;
			return true;
		}		
		return false;
	}	
	int h = hx(curr,sz);	
	if(d + h > maxd) return false;
	int u = encode(curr,sz),v;	
	
	int next[3];
	switch(sz){
		case 1: 
			for(auto x : G[curr[0]]){
				next[0] = x;				
				if(dfs(maxd,d+1,next,sz)) return true;
			}	
			break;
		case 2:
			for(auto x : G[curr[0]]){
				for(auto y : G[curr[1]]){						
					if(x==curr[1] && y== curr[0]) continue;
					if(x==y) continue;					
					next[0] = x;
					next[1] = y;										
					if(dfs(maxd,d+1,next,sz)) return true;
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
						if(dfs(maxd,d+1,next,sz)) return true;
					}
				}
			}
			break;
	}
	return false;		
}

bool ida(int sz){	
	int depth = hx(start,sz);
	bool ok = false;
	ans = inf;
	while(!dfs(depth,0,start,sz)){
		depth++;
	}
	return ok;
}

int main(){
	int n,m,sz;
	freopen("std.log","w",stderr);
	while(scanf("%d %d %d",&m,&n,&sz),n){		
		readGraph(n,m);
		for(int i=0;i<sz;i++) dijkstra(sz,i,end[i]);
		for(int i=0;i<sz;i++){
			for(int j=1;j<cnt;j++) fprintf(stderr,"%d %d : %d\n",p2xy[j][0],p2xy[j][1],dist[i][j]);
		}
		ida(sz);
		printf("%d\n",ans);
	}
	return 0;
}








