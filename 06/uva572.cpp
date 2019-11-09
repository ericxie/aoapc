#include <cstdio>

char a[111][111];

void dfs(int x,int y){
	int dx[8]={-1,-1,-1,0,0,1,1,1};
	int dy[8]={-1,0,1,-1,1,-1,0,1};
	if(a[x][y]=='@'){
		a[x][y] = '*';
		for(int i=0;i<8;i++) dfs(x+dx[i],y+dy[i]); 
	}
}

int count(int n,int m){
	int i,j,cnt=0;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) if(a[i][j]=='@'){
		cnt++;
		dfs(i,j);
	}
	return cnt;
}


int main(){
	int i,n,m;
	while(scanf("%d %d ",&n,&m),n&&m){
		for(i=1;i<=n;i++) gets(a[i]+1);
		printf("%d\n",count(n,m));
	}
	return 0;
}
