#include <cstdio>
#include <cstring>

int a[11][11][4];
int vis[11][11][4];
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

struct node{
	int x,y,d,prev;
	node() = default;
	node(int x,int y,int d,int prev):x(x),y(y),d(d),prev(prev){};
}Q[11*11*4];

int head,tail;
int sx,sy,sd,ex,ey;

void out(int n,int m){
	int i,j,k;
	for(i=0;i<=n+1;i++) for(j=0;j<=m+1;j++) {
		for(k=0;k<4;k++) printf("%x",a[i][j][k]);
		putchar(" \n"[j==m+1]);
	}
}

int getDir(char c){
	int i;
	char s[]="NESW";
	for(i=0;i<4 && s[i]!=c;i++);
	return i; 
}

int getPass(int dir,char *p){
	int ret = 0;
	while(*p){
		if(*p=='L') ret |= 1<< (dir + 3) % 4;
		else if(*p=='R') ret |= 1 << (dir + 1) % 4;
		else if(*p=='F') ret |= 1<< dir;
		p++;
	}
	return ret;
}

void read(){
	char c;
	int x,y,d;
	memset(a,0,sizeof(a));
	memset(vis,0,sizeof(vis));
	scanf("%d %d %c %d %d",&sx,&sy,&c,&ex,&ey);
	sd = getDir(c);
	sx += dx[sd], sy += dy[sd];
	char buf[9];
	while(scanf("%d",&x),x!=0){
		scanf("%d",&y);
		while(scanf("%s",buf),buf[0]!='*'){
			d = getDir(buf[0]);
			a[x][y][d] = getPass(d,buf+1);
			//printf("%d %d %d : %x\n",x,y,d,a[x][y][d]);
		}
	}
	//out(9,9);	
}

int bfs(){
	int x,y,d;
	head = tail = 0;
	Q[tail++] = node(sx,sy,sd,-1);
	vis[sx][sy][sd] = 1;
	while(head != tail){

		x = Q[head].x;
		y = Q[head].y;
		d = Q[head].d;
		//printf("%d %d %d: %x\n",x,y,d,a[x][y][d]);
		head++;
		if(x == ex && y == ey) return head - 1;
		for(int i=0;i<4;i++) if( a[x][y][d] & (1<<i) ) {
			if(!vis[x+dx[i]][y+dy[i]][i]){
				Q[tail++] = node(x+dx[i],y+dy[i],i,head-1);
				vis[x+dx[i]][y+dy[i]][i] = 1;
			}
		}
	}
	return -1;
}

void path(int idx,int &no){
	if(Q[idx].prev !=-1) path(Q[idx].prev,no);
	no++;
	if(no%10==1) printf("\n  ");
	else printf(" ");
	printf("(%d,%d)",Q[idx].x,Q[idx].y);
}

int main(){
	char name[111];
	while(scanf("%s",name),strcmp(name,"END")!=0){
		puts(name);
		read();
		int p = bfs();
		if(p==-1) puts("  No Solution Possible");
		else{
			int no = 1;
			printf("  (%d,%d)",sx-dx[sd],sy-dy[sd]);
			path(p,no);
			putchar('\n');
		}
	}
	return 0;
}
