#include <cstdio>
#include <algorithm>
#include <list>
#include <cstring>

char deg[9][9];
char curr[9][9];
char upp[9][9];
char mat[9][9];
int parent[99];
int n;

const int dx[]={0,0,1,1};
const int dy[]={0,1,0,1};

const int px[2][2]={{0,1},{1,0}};
const int py[2][2]={{0,1},{0,1}};

const char bar[]="\\/";


inline int id(int x,int y){
	return x * (n+1) + y;
}

inline int find(int u){
	while(parent[u]>=0) u = parent[u];
	return u;
}

inline int connect(int x1,int y1,int x2,int y2){
	int u = find(id(x1,y1));
	int v = find(id(x2,y2));
	if(u == v) return 0;
	curr[x1][y1]++,curr[x2][y2]++;
	if(parent[u] < parent[v]) std::swap(u,v);
	parent[u] += parent[v];
	parent[v] = u;	
	return 1;
}

inline void link(int x,int y,int k){
	int i;
	if(connect(x+px[k][0],y+py[k][0],x+px[k][1],y+py[k][1])){
		for(i=0;i<4;i++) upp[x+dx[i]][y+dy[i]]--;
		mat[x][y] = bar[k];		
	}		
}

void preprocess(int n){
	int i,j;
	//
	memset(mat,'.',sizeof(mat));
	memset(curr,0,sizeof(curr));
	memset(parent,-1,sizeof(parent));
	//
	upp[0][0] = upp[0][n] = upp[n][0] = upp[n][n] = 1;
	for(j=1;j<n;j++) upp[0][j] = upp[n][j] = 2;
	for(i=1;i<n;i++) upp[i][0] = upp[i][n] = 2;
	for(i=1;i<n;i++) for(j=1;j<n;j++) upp[i][j] = 4;
	//4个角
	
	if(deg[0][0]==0) link(0,0,1);
	else if(deg[0][0]==1) link(0,0,0);

	if(deg[0][n]==0) link(0,n-1,0);
	else if(deg[0][n]==1) link(0,n-1,1);

	if(deg[n][0]==0) link(n-1,0,0);
	else if(deg[n][0]==1) link(n-1,0,1);

	if(deg[n][n]==0) link(n-1,n-1,1);
	else if(deg[n][n]==1) link(n-1,n-1,0);
	//4条边为0或者2	
	for(j=1;j<n;j++) {		
		if(deg[0][j] == 0) link(0,j-1,0),link(0,j,1);
		else if(deg[0][j] == 2) link(0,j-1,1),link(0,j,0);
	}
	
	for(j=1;j<n;j++) {
		if(deg[n][j] == 0) link(n-1,j-1,1),link(n-1,j,0);
		else if(deg[n][j] == 2) link(n-1,j-1,0),link(n-1,j,1);
	}
	
	for(i=1;i<n;i++){
		if(deg[i][0] == 0) link(i-1,0,0),link(i,0,1);
		else if(deg[i][0] == 2) link(i-1,0,1),link(i,0,0);
	}

	for(i=1;i<n;i++){
		if(deg[i][n] == 0) link(i-1,n-1,1),link(i,n-1,0);
		else if(deg[i][n] == 2) link(i-1,n-1,0),link(i,n-1,1);
	}
	
	
	//中间点为0或者4
	for(i=1;i<n;i++) for(j=1;j<n;j++){
		if(deg[i][j] == 0) link(i-1,j-1,1),link(i-1,j,0),link(i,j-1,0),link(i,j,1);
		else if(deg[i][j] == 4) link(i-1,j-1,0),link(i-1,j,1),link(i,j-1,1),link(i,j,0);
	}
	
	//4条边为1的情况
	for(j=1;j<n;j++) if(deg[0][j] == 1){
		if(mat[0][j-1] == '/') link(0,j,1);
		else if(mat[0][j-1] == '\\') link(0,j,0);
		else if(mat[0][j] == '/') link(0,j-1,1);
		else if(mat[0][j] == '\\') link(0,j-1,0);
	}

	for(j=1;j<n;j++) if(deg[n][j] == 1){
		if(mat[n-1][j-1] == '/') link(n-1,j,1);
		else if(mat[n-1][j-1] == '\\') link(n-1,j,0);
		else if(mat[n-1][j] == '/') link(n-1,j-1,1);
		else if(mat[n-1][j] == '\\') link(n-1,j-1,0);
	}

	for(i=1;i<n;i++) if(deg[i][0] == 1){
		if(mat[i-1][0] == '/') link(i,0,1);
		else if(mat[i-1][0] == '\\') link(i,0,0);
		else if(mat[i][0] == '/') link(i-1,0,1);
		else if(mat[i][0] == '\\') link(i-1,0,0);
	}

	for(i=1;i<n;i++) if(deg[i][n] == 1){
		if(mat[i-1][n-1] == '/') link(i,n-1,1);
		else if(mat[i-1][n-1] == '\\') link(i,n-1,0);
		else if(mat[i][n-1] == '/') link(i-1,n-1,1);
		else if(mat[i][n-1] == '\\') link(i-1,n-1,0);
	}	
}	

inline int valid(int x,int y){
	if(deg[x][y] == -1) return 1;
	return curr[x][y] <= deg[x][y] && curr[x][y] + upp[x][y] >= deg[x][y];
}

int dfs(int x,int y);

int draw(int x,int y,int k){
	int i,x1,y1,x2,y2,u,v,t;
	x1 = x+px[k][0], y1 = y+py[k][0];
	x2 = x+px[k][1], y2 = y+py[k][1]; 
	//fprintf(stderr,"%d %d %d : %d %d %d %d\n",x,y,k,x1,y1,x2,y2);
	curr[x1][y1]++,curr[x2][y2]++;
			
	for(i=0;i<4;i++) {
		//fprintf(stderr,"%d :%d %d %d\n",i,curr[x+dx[i]][y+dy[i]],upp[x+dx[i]][y+dy[i]],deg[x+dx[i]][y+dy[i]]);	
		if(!valid(x+dx[i],y+dy[i])) break;
	}
	if(i==4){
		u = find(id(x1,y1));
		v = find(id(x2,y2));
		if(u == v) goto next;
		if(parent[u] < parent[v]) std::swap(u,v);
		parent[u] += parent[v];
		t = parent[v];
		parent[v] = u;
		//fprintf(stderr,"%d %d : %d %d\n",u,v,parent[u],parent[v]);
		mat[x][y]=bar[k];	
		//for(int j = 0; j<n;j++) fprintf(stderr,"%s\n",mat[j]);			
		if(dfs(x,y+1)) return 1;
		mat[x][y]='.';
		parent[u] -= t;
		parent[v] = t;
		//fprintf(stderr,"%d %d : %d %d\n",u,v,parent[u],parent[v]);
	}
next:
	curr[x1][y1]--,curr[x2][y2]--;
	return 0;
}

int dfs(int x,int y){
	int i;
	
	for(;;){
		if(y == n) x++,y=0;
		if(x == n) return 1;
		//fprintf(stderr,"%d %d %c\n",x,y,mat[x][y]);
		if(mat[x][y]=='.') break;
		for(i=0;i<4;i++) {
			int cx = x+dx[i];
			int cy = y+dy[i];
			//fprintf(stderr,"   %d : %d %d %d\n",i,curr[cx][cy],upp[cx][cy],deg[cx][cy]);
			if(!valid(cx,cy)) return 0;
		}
		y++;
	}	

	for(i=0;i<4;i++) upp[x+dx[i]][y+dy[i]]--;
	if(draw(x,y,0)) return 1;
	if(draw(x,y,1)) return 1;	
	for(i=0;i<4;i++) upp[x+dx[i]][y+dy[i]]++;
	return 0;
}

int main(){
	int T,i,j;
	//freopen("11694.log","w",stderr);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);		
		for(i=0;i<=n;i++){
			scanf("%s",deg[i]);
			for(j=0;j<=n;j++) {				
				if(deg[i][j] != '.') deg[i][j] -= '0';
				else deg[i][j] = -1;
				//fprintf(stderr,"%d %d : %d\n",i,j,deg[i][j]);
			}
		}
		preprocess(n);
		for(i=0;i<n;i++) mat[i][n] = 0;
		dfs(0,0);		
		for(i=0;i<n;i++) puts(mat[i]);
	}
	return 0;
}