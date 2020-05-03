#include <cstdio>
#include <queue>
#include <cstring>

struct node{
	int x,y,s,k;
	node(int x=0,int y=0,int s=0,int k=0):x(x),y(y),s(s),k(k){};
	bool operator<(const node &rhs) const{
		if(s == rhs.s) return k > rhs.k;
		return s > rhs.s;
	}
};

int grids[22][22];
int cost[22][22][22];
int lmt;
int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};

int bfs(int n,int m){
	std::priority_queue<node> Q;
	int k = grids[1][1];
	Q.emplace(1,1,0,k);
	memset(cost,0x3f,sizeof(cost));
	cost[1][1][k] = 0;
	while(!Q.empty()){
		auto u = Q.top();
		Q.pop();
		fprintf(stderr,"%d %d %d %d\n",u.x,u.y,u.s,u.k);
		if(u.x == n && u.y == m) return u.s;
		for(int i=0; i<4; i++){
			int nx = u.x + dx[i];
			int ny = u.y + dy[i];
			if(grids[nx][ny] == -1) continue;
			if(grids[nx][ny] == 0 && u.s + 1 < cost[nx][ny][0])	{
				Q.emplace(nx,ny,u.s + 1, 0);
				cost[nx][ny][0] = u.s + 1;	
			} else if(u.k < lmt && u.s + 1 < cost[nx][ny][u.k+1]){
				Q.emplace(nx,ny,u.s + 1, u.k + 1);
				cost[nx][ny][u.k + 1] = u.s + 1;
			}		
		}
	}
	return -1;	
}

int main(){
	int T,n,m,i,j;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&lmt);
		memset(grids,-1,sizeof(grids));
		for(i=1;i<=n;i++)for(j=1;j<=m;j++) scanf("%d",&grids[i][j]);		
		printf("%d\n",bfs(n,m));
	}
	return 0;

}