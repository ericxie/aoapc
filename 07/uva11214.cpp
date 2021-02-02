#include <cstdio>
#include <cstring>

const int N = 10;
char board[N][N];
char row[N],col[N],lr[N<<1],rl[N<<1];
int n,m,maxd;

inline bool check(){
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<m;j++) if(board[i][j] && row[i] && col[j] && lr[i+j] && rl[n-1-i+j]) return 0; 
	return 1;
}

int dfs(int x,int y,int d){
	int _col,_row,_lr,_rl;
	if(d == maxd) return check();
	for(int i = x; i < n; i++)
		for(int j = y; j < m; j++) if(row[i] || col[j] || lr[i+j] || rl[n-1-i+j]){
			_row = row[i], _col = col[j], _lr = lr[i+j], _rl = rl[n-1-i+j];
			row[i] = col[j] = lr[i+j] = rl[n-1-i+j] = 0;			
			int nx,ny;
			if(y==m-1) nx = x+1,ny = 0;
			else nx = x, ny = y+1;
			if(dfs(nx,ny,d+1))	return 1;
			row[i] = _row , col[j] =  _col , lr[i+j] = _lr, rl[n-1-i+j] = _rl;
	} 
	return 0;
}

int main(){
	int k=0,i,j;
	char ch;
	//freopen("11214.log","w",stderr);
	while(scanf("%d",&n),n){
		scanf("%d",&m);
		getchar();	
		memset(board,0,sizeof(board));	
		memset(col,0,sizeof(col));
		memset(row,0,sizeof(row));
		memset(lr,0,sizeof(lr));
		memset(rl,0,sizeof(rl));
		for(i=0;i<n;i++) {
			for(j=0;j<m;j++){
				ch = getchar();
				if(ch == 'X') {		
					board[i][j]=row[i]=col[j]=lr[i+j]=rl[n-1-i+j]=1;
				}
			}
			getchar();
		}

		printf("Case %d: ",++k);		
		for(maxd=0;;maxd++) if(dfs(0,0,0)) {
			printf("%d\n",maxd);
			break;
		}

	}
	return 0;
}