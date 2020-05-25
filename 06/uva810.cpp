#include <map>
#include <tuple>
#include <utility>
#include <stack>
#include <set>
#include <cstring>

#define fprintf 0&&fprintf

const int dice[7][4] = 	{ {0,0,0,0},
						  {2,3,5,4},
						  {1,4,6,3},
						  {1,2,6,5},
						  {5,6,2,1},
						  {3,6,4,1},
						  {4,5,3,2}
		                };

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int maze[12][12];

struct node{
	int x,y,top,face,prev;
	node(int x,int y,int top, int face):x(x),y(y),top(top),face(face),prev(-1){};
	node(const node &t):x(t.x),y(t.y),top(t.top),face(t.face),prev(-1){};
	node() = default;
	void move(int dir){
		int i;
		x += dx[dir];
		y += dy[dir];
		switch(dir){
			case 0:
			case 1:
				for(i=0;i<4 && dice[top][i]!= face;i++);
				i = (i + (dir?-1:1) + 4) % 4;
				top = dice[top][i]; 
				break;	
			case 2:
				i = 7 - top;
				top = face;
				face = i;
				break;
			case 3:
				i = 7 - face;
				face = top;
				top = i;
				break;
		}
		out("   +");	
	}
	inline bool valid(int dir){
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		fprintf(stderr,"%d %d : %d\n",nx,ny,maze[nx][ny]);
		if(maze[nx][ny] == -1 || maze[nx][ny] == top) {
			move(dir);
			return true;
		}
		return false;
	}	
	inline bool operator <(const node &rhs) const{
		return std::make_tuple(x,y,top,face) < std::make_tuple(rhs.x,rhs.y,rhs.top,rhs.face);
	}
	inline void out(const char *s){
		fprintf(stderr,"%s - %d,%d : %d %d\n",s,x,y,top,face);
	}
};

std::set<node> vis;
node Q[10*10*6*6 + 11];
int head,tail;

void print_path(int p){
	std::stack<std::pair<int,int>> s;
	for(;p!=-1;p=Q[p].prev) s.push(std::make_pair(Q[p].x,Q[p].y));
	int n = 0;
	while(!s.empty()){
		if(n==0) printf("\n  ");
		else printf(",");
		auto t = s.top();
		s.pop();
		printf("(%d,%d)",t.first,t.second);
		n++;
		if(n==9){
			if(s.empty()) putchar('\n');
			else putchar(',');
			n = 0;
		}
	}
	if(n!=0) putchar('\n');
}

bool bfs(node s){	
	vis.clear();
	head = tail = 0;
	Q[tail++] = s;
	while(head != tail){
		auto t = Q[head++];
		t.out("node");
		if(t.x == s.x && t.y == s.y && head != 1) {
			print_path(head-1);
			return true;
		}
		for(int i = 0; i < 4; i++){
			node next = node(t);
			next.prev = head - 1;
			if(next.valid(i) && vis.find(next) == vis.end()){
				vis.insert(next);
				Q[tail++] = next;
			}
		}
	}
	return false;
}

int main(){
	char str[111];
	while(scanf("%s",str),strcmp(str,"END")!=0){
		printf(str);
		int i,j,n,m,x,y,top,face;
		scanf("%d %d %d %d %d %d",&n,&m,&x,&y,&top,&face);
		memset(maze,0,sizeof(maze));
		for(i=1;i<=n;i++) for(j=1;j<=m;j++) scanf("%d",&maze[i][j]);
		if(!bfs(node(x,y,top,face))) puts("\n  No Solution Possible");
	}	
	return 0;
}
