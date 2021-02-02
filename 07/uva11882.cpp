#include <cstdio>
#include <string>
#include <cstring>

char mat[17][17];
int vis[17][17];
int tag[17][17];

const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
std::string best;

void init(int n,int m){
	int i,j;
	for(i=0;i<=n+1;i++) vis[i][0] = vis[i][m+1] = 1;
	for(j=0;j<=m+1;j++) vis[0][j] = vis[n+1][j] = 1;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) vis[i][j] = (mat[i][j] == '#');	
}

int dfs1(int x,int y){
	int cnt = 1;	
	tag[x][y] = 1;
	for(int i = 0 ;i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!tag[nx][ny]) cnt += dfs1(nx,ny);
	}
	return cnt;	
}

void dfs(std::string &s,int x,int y){
	s.push_back(mat[x][y]);	
	int sl = s.size();
	int bl = best.size();
	//fprintf(stderr,"%d,%d : %s | %s\n",x,y,best.c_str(),s.c_str());
	if(sl > bl || (sl == bl && s > best)) best = s; 
	else {
		std::string t = s;
		t.push_back(char('9'+1));
		memcpy(tag,vis,sizeof(vis));
		int h = dfs1(x,y);
		//fprintf(stderr,"%d %d %d\n",sl,h,bl);	
		if(sl + h - 1 < bl || (sl + h - 1 == bl && t < best)) goto end;
	}
	vis[x][y] = 1;	
	for(int i = 0 ;i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!vis[nx][ny]) dfs(s,nx,ny);
	}
	vis[x][y] = 0;
end:	
	s.pop_back();	
}

inline void solve(int n,int m){
	int i,j;
	std::string s="";
	best = "";
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(!vis[i][j]){		
		dfs(s,i,j);			
	}
	puts(best.c_str());
}

int main(){
	int n,m;
	while(scanf("%d %d",&n,&m),n){
		for(int i=1;i<=n;i++) scanf("%s",mat[i]+1);		
		init(n,m);
		solve(n,m);
	}
	
	return 0;
}


