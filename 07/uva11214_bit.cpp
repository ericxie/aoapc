#include <cstdio>
#include <cstring>
typedef unsigned int uint;
const int N = 10;
char board[N][N];
//char row[N],col[N],lr[N<<1],rl[N<<1];

#define set(x,p) ((x) |= (1 << (p)))
#define clr(x,p) ((x) & ~(1 << (p)))
#define is1(x,p) ((x) &  (1 << (p)))
int n,m,maxd;

inline bool check(int row,int col,int lr,int rl){
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<m;j++) if(board[i][j] && is1(row,i) && is1(col,j) && is1(lr,i+j) && is1(rl,n-1-i+j) ) return 0; 
	return 1;
}

int dfs(int x,int y,int d,uint row,uint col,uint lr,uint rl){	
	if(d == maxd) return check(row,col,lr,rl);
	for(int i = x; i < n; i++)
		for(int j = y; j < m; j++) if(is1(row,i) || is1(col,j) || is1(lr,i+j) || is1(rl,n-1-i+j)){					
			int nx,ny;
			if(y==m-1) nx = x+1,ny = 0;
			else nx = x, ny = y+1;
			if(dfs(nx,ny,d+1,clr(row,i),clr(col,j),clr(lr,i+j),clr(rl,n-1-i+j))) return 1;
	} 
	return 0;
}

int main(){
	int k=0,i,j;
	char ch;
	uint row,col,lr,rl;
	//freopen("11214.log","w",stderr);
	while(scanf("%d",&n),n){
		scanf("%d",&m);
		getchar();	
		memset(board,0,sizeof(board));	
		row=col=lr=rl=0;
		for(i=0;i<n;i++) {
			for(j=0;j<m;j++){
				ch = getchar();
				if(ch == 'X') {		
					board[i][j]=1;
					set(row,i);
					set(col,j);
					set(lr,i+j);
					set(rl,n-1-i+j);
				}
			}
			getchar();
		}

		printf("Case %d: ",++k);		
		for(maxd=0;;maxd++) if(dfs(0,0,0,row,col,lr,rl)) {
			printf("%d\n",maxd);
			break;
		}

	}
	return 0;
}