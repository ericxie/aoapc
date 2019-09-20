#include <cstdio>
#include <cstring>


char board[12][11];

struct chess{
	int c,x,y;
}red[7];

inline int in_black(int x,int y){
	return (x>=1 && x <=3 && y>=4 && y<=6);
}

int pao(int x,int y,int cx,int cy){
	int i,c=0;
	if(x == cx){
		if(y < cy)  for(i=y+1;i<cy;i++) c += board[x][i];
		else for(i=cy+1;i<y;i++) c +=  board[x][i];
	} else if(y == cy){
		if(x < cx)  for(i=x+1;i<cx;i++) c += board[i][y];
		else for(i=cx+1;i<x;i++) c +=  board[i][y]; 
	}
	return c==1;
}

int ma(int x,int y,int cx,int cy){
	const int dx[8]={-1,1,2,2,1,-1,-2,-2};
	const int dy[8]={-2,-2,-1,1,2,2,1,-1};
	const int bx[8]={0,0,1,1,0,0,-1,-1};
	const int by[8]={-1,-1,0,0,1,1,0,0};
	int i,nx,ny;
	for(i=0;i<8;i++){
		nx = x + dx[i];
		ny = y + dy[i];
		if(!board[x+bx[i]][y+by[i]] && in_black(nx,ny) && nx == cx && ny == cy) return 1; 
	}
	return 0;
}

int ju(int x,int y,int cx,int cy){	
	int i;
	if(x == cx){
		if(y < cy)  {
			for(i=y+1;i<cy;i++) if(board[x][i]) return 0;
		} else {
			for(i=cy+1;i<y;i++) if(board[x][i]) return 0;
		}
		return 1;
	} else if(y == cy){
		if(x < cx) {
			for(i=x+1;i<cx;i++)  if(board[i][y]) return 0;
		} else {
			for(i=cx+1;i<x;i++) if(board[i][y]) return 0;
		}
		return 1;
	}
	return 0;
}

int check(int cx,int cy,int n){
	int i,flag;
	int (*pf[4])(int,int,int,int)={pao,ma,ju,ju};
	chess *p = red;
	for(i=0;i<n;i++,p++){
		if(cx == p->x && cy == p->y) continue;
		flag = (*pf[p->c])(p->x,p->y,cx,cy);
		//printf("%d %d, %d %d %d %d\n",cx,cy,p->c,p->x,p->y,flag);
		if(flag) return 1;
	}
	return 0;
}

int type(char c){
	const char s[5]="CHRG";
	int i;
	for(i=0;i<4&&s[i]!=c;i++);
	return i; 
}

int main(){
	int i,n,cx,cy,x,y,rx,ry;
	char c;
	const int dx[5]={0,0,0,-1,1};
	const int dy[5]={0,-1,1,0,0};
	
	while(scanf("%d %d %d",&n,&cx,&cy),n){
		memset(board,0,sizeof(board));
		for(i=0;i<n;i++){
			scanf(" %c %d %d",&c,&rx,&ry);
			red[i].c = type(c);
			red[i].x = rx;
			red[i].y = ry;
			board[rx][ry] = 1;
		}
		for(i=0;i<5;i++){
			x = cx + dx[i];
			y = cy + dy[i];
			if(in_black(x,y) && !check(x,y,n)){
				puts("NO");
				break;
			}
		}
		if(i==5) puts("YES");
	}
	return 0;
}