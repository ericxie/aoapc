#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 222;
const int bgc = 2;
int buf[N][N];
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
const int hex[16][4] = {{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},
                      	 {0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},
                      	 {1,0,0,0},{1,0,0,1},{1,0,1,0},{1,0,1,1},
                      	 {1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}};

void read(int n,int m){
	int i,j,x,k;
	memset(buf,0,sizeof(buf));
	for(i=0;i<=n+3;i++) buf[i][0] = buf[i][m+3] = bgc;
	for(j=0;j<=m+3;j++) buf[0][j] = buf[n+3][j] = bgc; 
	for(i=2;i<=n+1;i++) for(j=2;j<=m+1;j+=4){
		scanf("%1x",&x);
		for(k=0;k<4;k++) buf[i][j+k] = hex[x][k];
	}
}

void out(int n,int m){
	for(int i=0;i<=n+3;i++) {
		for(int j=0;j<=m+3;j++) printf("%d",buf[i][j]);
		putchar('\n');
	}
}

void dfs0(int x,int y){
	if(buf[x][y] == 0){
		buf[x][y] = bgc;
		for(int i = 0; i < 4 ;i++) dfs0(x+dx[i],y+dy[i]);
	}
}

int dfs1(int x, int y){
	int cnt = 0;
	if(buf[x][y]==1){
		buf[x][y] = bgc;
		for(int i=0;i<4;i++) cnt += dfs1(x+dx[i],y+dy[i]);
	} else if(buf[x][y] == 0){
		cnt++;
		dfs0(x,y);
	}
	return cnt;
}

std::vector<char> ans;

void dfu(int n,int m){
	int i,j;
	char s[7]="WAKJSD";
	for(i=2;i<=n+1;i++) for(j=2;j<=m+1;j++) if(buf[i][j] == 1){
		ans.push_back(s[dfs1(i,j)]);
	}
}

int main(){
	int n,m,T=0;
	while(scanf("%d %d",&n,&m),n&&m){
		ans.clear();
		m <<= 2;
		read(n,m);		
		dfs0(1,1);
		dfu(n,m);
		std::sort(ans.begin(),ans.end());
		printf("Case %d: ",++T);
		for(auto c : ans) putchar(c);
		putchar('\n');
	}
	return 0;
}