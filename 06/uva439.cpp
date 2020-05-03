#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

int chess[12][12];
const int dx[8] = {-1,-2,-2,-1,1,2,2,1};
const int dy[8] = {-2,-1,1,2,2,1,-1,-2};

int bfs(int sx,int sy,int ex,int ey){
	memset(chess,-2,sizeof(chess));
	for(int i=2;i<10;i++) for(int j=2;j<10;j++) chess[i][j] = -1;
	std::queue<std::pair<int,int> > Q;
	Q.emplace(2+sx,2+sy);
	chess[2+sx][2+sy] = 0;
	while(!Q.empty()){
		auto xy = Q.front();
		int x = xy.first;
		int y = xy.second;
		if(x==2+ex && y==2+ey) return chess[x][y];
		Q.pop();
		for(int i=0;i<8;i++) if(chess[x+dx[i]][y+dy[i]]==-1){			
			chess[x+dx[i]][y+dy[i]] = chess[x][y] + 1;			
			Q.emplace(x+dx[i],y+dy[i]);
		}
	}
	return -1;
}

int main(){
	char a[3],b[3];
	while(~scanf("%s %s",a,b)){		
		printf("To get from %s to %s takes %d knight moves.\n",a,b,bfs(a[0]-'a',a[1]-'1',b[0]-'a',b[1]-'1'));
	}	
	return 0;
}