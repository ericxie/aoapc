#include <cstdio>
#include <cstring>
const int N = 8;
int board[N+2][N+2];
int mx[N*N],my[N*N];
const int dx[8]={-1,-1,-1,0,1,1,1,0};
const int dy[8]={-1,0,1,1,1,0,-1,-1};

int check(int cx,int cy,int c){
	int x,y,i,j,p;
	p = c ^ 1;
	for(i=0;i<8;i++){
		x = cx ,y = cy;
		for(j=1;;j++){
			x += dx[i];
			y += dy[i];
			if(board[x][y]==c){
				if(j>1) return 1;
				else break;
			} else if(board[x][y]!=p) break;
		}
	}
	return 0;
}

int getMoves(int c){
	int i,j,cnt=0;
	for(i=1;i<=N;i++) for(j=1;j<=N;j++) {
		if(board[i][j] == 1 && check(i,j,c)){
			mx[cnt] = i;
			my[cnt] = j;
			cnt++;
		}
	}
	return cnt;
}

void _list(int c){
	int i,cnt;
	cnt = getMoves(c);
	if(cnt){
		for(i=0;i<cnt;i++) printf("(%d,%d)%c",mx[i],my[i]," \n"[i==cnt-1]);
	} else {
		puts("No legal move.");
	}
}

void stat(){
	int i,j,b=0,w=0;
	for(i=1;i<=N;i++) for(j=1;j<=N;j++) 
		if(board[i][j]==2) w++; 
		else if(board[i][j]==3) b++;
	printf("Black - %2d White - %2d\n",b,w); 
}

void move(int cx,int cy,int c){
	int x,y,i,j,k,p=c^1;
	board[cx][cy] = c;
	for(i=0;i<8;i++){
		x = cx + dx[i], y = cy + dy[i];
		for(j=1;board[x][y]==p;j++){
			x += dx[i];
			y += dy[i];
		}
		if(board[x][y]==c){
			x = cx + dx[i], y = cy + dy[i];
			for(k=1;k<j;k++){
				board[x][y] = c;
				x += dx[i];
				y += dy[i];		
			}
		}
	}
}

void out(){
	int i,j;
	const char c[]="\n-WB";
	for(i=1;i<=N;i++) for(j=1;j<=N+1;j++)  putchar(c[board[i][j]]);
}

void readBoard(){
	int i,j;
	char c;
	memset(board,0,sizeof(board));
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			c=getchar();
			if(c=='-') board[i][j] = 1;
			else if(c == 'W') board[i][j] = 2;
			else if(c == 'B') board[i][j] = 3;
		}
		getchar();
	}
}

int main(){
	int T,player;
	char c;
	scanf("%d",&T);
	while(T--){
		getchar();
		readBoard();
		c = getchar();
		if(c=='W') player=2;
		else player = 3;
		getchar();
		while(c=getchar(),c!='Q'){
			if(c=='L') _list(player);
			else {
				int cnt = getMoves(player);
				int x,y;
				c = getchar();
				x = c - '0';
				c = getchar();
				y = c - '0';
				//printf("---%d %d %d %d\n",cnt,player,x,y);
				if(!cnt)	player ^=1;
				
				move(x,y,player);
				stat();
				player^=1;
			}			
			getchar();
		}
		out();
		if(T) puts("");
	}
	return 0;
}