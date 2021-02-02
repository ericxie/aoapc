#include <cstdio>
#include <queue>
#include <unordered_set>
#include <string>

struct node{
	int s,x,y;
	long long maze;
	std::string path;
	node(){ s = x = y = maze = 0; path = "";}
	node(int _s,int _x,int _y,long long _maze,std::string & _path):s(_s),x(_x),y(_y),maze(_maze),path(_path){}
	node(const node &rhs){ *this = rhs; }
	inline long long id(){
		long long r = x * 6 + y;
		r <<= 58;
		r |= maze;
		return r; 
	}
};

int grid[4][6][4];

void wall(){
	int i,j,t;
	for(i=0;i<4;i++) for(j=0;j<6;j++) {
		t = i * 13 + j;
		grid[i][j][0] = t + 6;
		grid[i][j][1] = t 	 ;
		grid[i][j][2] = t + 7;
		grid[i][j][3] = t +13;
		//fprintf(stderr,"%d %d : %d %d %d %d\n",i,j,grid[i][j][0],grid[i][j][1],grid[i][j][2],grid[i][j][3]);
	}
}

const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};
const char dir[]="WNES";

std::unordered_set<long long> vis;

int bfs(int x,int y,long long maze){
	std::queue<node> Q;
	std::unordered_set<long long> vis;
	std::string path = "";
	Q.emplace(0,x,y,maze,path);
	while(!Q.empty()){
		node u = Q.front();
		Q.pop();
		int x = u.x;
		int y = u.y;
		maze = u.maze;
		//fprintf(stderr,"%d %d %d: %s\n",u.x,u.y,u.s,u.path.c_str());
		for(int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			path = u.path + dir[k];
			//fprintf(stderr,"%d %d | %d %d : %d\n",x,y,nx,ny,k);
			if(~maze & (1LL << grid[x][y][k])){				
				if(nx < 0 || nx > 3 || ny < 0 || ny > 5) {
					printf("%s\n",path.c_str());
					return 1;
				};
				//fprintf(stderr,"%s+%c\n",u.path.c_str(),dir[k]);
				node v = node(u.s+1,nx,ny,maze,path);
				long long id = v.id();
				if(vis.find(id)!=vis.end()) continue;
				//fprintf(stderr,"ok\n");
				vis.insert(id);
				Q.push(v);
			} else {
				if(nx < 0 || nx > 3 || ny < 0 || ny > 5) continue;
				//fprintf(stderr,"%d %d %d: %d\n",nx,ny,grid[nx][ny][k],(maze & (1LL << grid[nx][ny][k])) != 0);
				if(~maze & (1LL << grid[nx][ny][k])){
					//fprintf(stderr,"%s*%c\n",u.path.c_str(),dir[k]);
					long long next = maze & ~(1LL << grid[x][y][k]);
					next |= 1LL << grid[nx][ny][k];
					node v = node(u.s+1,nx,ny,next,path);
					long long id = v.id();
					if(vis.find(id)!=vis.end()) continue;
					//fprintf(stderr,"ok\n");
					vis.insert(id);
					Q.push(v);
				}
			}
		}
	}
	return 0;
}

int main(){
	freopen("10384.log","w",stderr);
	wall();
	int x,y,i,j,k,t;
	long long maze;

	while(scanf("%d %d",&y,&x),x){
		x--,y--;
		maze = 0;
		for(i=0;i<4;i++) for(j=0;j<6;j++) {
			scanf("%d",&t);
			for(k=0;k<4;k++) if(t & (1 << k)){
				maze |= 1LL << grid[i][j][k];
			}
		}
		bfs(x,y,maze);
	}
	return 0;
}