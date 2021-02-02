#include <cstdio>
#include <cstring>
#include <queue>
/*
      | up/down 0 | left/right 1
------+-----------+-------------
0 WRB | 2 RWB     | 5 BRW
1 WBR | 4 BWR     | 3 RWB
2 RWB | 0 WRB     | 4 BWR
3 RBW | 5 BRW     | 1 WBR
4 BWR | 1 WBR     | 2 RWB
5 BRW | 3 RBW     | 0 WRB
*/
int T[6][2]={
2,5,
4,3,
0,4,
5,1,
1,2,
3,0	
};

const int sz = 1679616; // 6^8

int step[3][3][sz],color[3][3][sz];

// 0：up, 1 : right, 2: down, 3:left
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};

struct Node{
	int x,y,t;
	Node() = default;
	Node(int _x,int _y,int _t) : x(_x),y(_y),t(_t){}
};

inline void decode(int *a,const Node &u){
	int i,j,k=8,t = u.t;
	for(i=2;i>=0;i--) for(j=2;j>=0;j--,k--) {
		if(i == u.x && j == u.y) a[k] = -1;
		else{
			a[k] = t % 6;
			t /= 6;	
		}		
	}
}

inline int encode(int *a){
	int i,j,k=0;
	int t = 0;
	for(i=0;i<3;i++) for(j=0;j<3;j++,k++){
		if(a[k]!=-1){
			t *= 6;
			t += a[k];
		}
	}
	return t;
}

typedef std::queue<Node> Queue;

inline void emplace(Queue &Q,int x,int y,int t,int s,int c){
	step[x][y][t] = s;
	color[x][y][t] = c;
	Q.emplace(Node(x,y,t));
}

inline void out(int *u,int *v){
	int i,j;
	const char s[]="EWWRRBB";
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) printf("%c",s[u[i*3+j]+1]);
		putchar(' ');
		for(j=0;j<3;j++) printf("%c",s[v[i*3+j]+1]);
		putchar('\n');
	}
	putchar('\n');
}

void init_end(Queue &Q,int ex,int ey,char *et,int k,int t){
	if(k==8) {
		emplace(Q,ex,ey,t,0,2);
		return;
	}
	t *= 6;
	if(et[k]=='W'){
		init_end(Q,ex,ey,et,k+1,t);
		init_end(Q,ex,ey,et,k+1,t+1);
	} else if(et[k] == 'R'){
		init_end(Q,ex,ey,et,k+1,t+2);
		init_end(Q,ex,ey,et,k+1,t+3);
	} else if(et[k] == 'B'){
		init_end(Q,ex,ey,et,k+1,t+4);
		init_end(Q,ex,ey,et,k+1,t+5);
	}
}

inline int check(char *et){
	for(int i=0;i<8;i++) if(et[i]!='W') return 0;
	return 1;
}

int dbfs(int sx,int sy,int ex,int ey,char *et){	
	Queue Q;
	int um[9],vm[9];	
	if(sx == ex && sy == ey && check(et)) return 0;
	memset(step,-1,sizeof(step));
	memset(color,0,sizeof(color));	

	emplace(Q,sx,sy,0,0,1);
	init_end(Q,ex,ey,et,0,0);
	while(!Q.empty()){
		auto u  = Q.front();
		Q.pop();
		//fprintf(stderr,"%d %d %d : %d %d\n",u.x,u.y,u.t,step[u.x][u.y][u.t],color[u.x][u.y][u.t]);
		int us = step[u.x][u.y][u.t];
		int uc = color[u.x][u.y][u.t];
		if(uc == 1 && us == 21 || uc==2 && us == 9 ) continue;
				
		decode(um,u);
		int uid = u.x * 3 + u.y;
		for(int i=0;i<4;i++){ // 0：up, 1 : right, 2: down, 3:left
			if((u.y==0 && i==3) || 
			   (u.y==2 && i==1) ||
			   (u.x==0 && i==0) ||
			   (u.x==2 && i==2)) continue; 
			int vx = u.x + dx[i];
			int vy = u.y + dy[i];
			int vid = vx * 3 + vy;
			memcpy(vm,um,sizeof(vm));
			int c = um[vid];
			vm[uid] = T[c][i&1];
			vm[vid] = -1;			
			int t = encode(vm);
			if(step[vx][vy][t]==-1){
				emplace(Q,vx,vy,t,us+1,uc);
				//out(um,vm);
			} else {
				int flag = uc | color[vx][vy][t];
				if(flag == 3) return us+step[vx][vy][t]+1;
			}
		}
	}
	return -1;	
}


int main(){
	int i,j,sx,sy,ex,ey,t;
	char ch,et[8];
	
	while(scanf("%d %d",&sy,&sx),sx){
		sx--,sy--;
		
		for(i=t=0;i<3;i++) for(j=0;j<3;j++) {
			scanf(" %c",&ch);	
			if(ch == 'E'){
				 ex = i ,ey = j;
				 continue;
			}		
			et[t++] = ch;   
		}
		
		//for(i=0;i<3;i++) for(j=0;j<3;j++) fprintf(stderr,"%c%c",des[i][j]," \n"[j==2]);
		printf("%d\n",dbfs(sx,sy,ex,ey,et));
	}
	return 0;
}

