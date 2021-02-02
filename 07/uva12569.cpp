#include <cstdio>
#include <queue>
#include <list>
#include <cstring>

// 15bit  | 4bit
// status | robot
#define set(x,p) (x |  (1<<(p)))
#define clr(x,p) (x & ~(1<<(p)))
int dist[1<<19];
int prev[1<<19][3];
std::list<int> G[15];

inline void note(int v,int u,int from,int to){
	prev[v][0] = u;
	prev[v][1] = from;
	prev[v][2] = to;
}

int bfs(int st,int end,int sz){
	std::queue<int> Q;
	memset(dist,-1,sizeof(dist));
	Q.push(st);
	dist[st] = 0;
	note(st,-1,0,(st&0xf)+1);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		int robo = u & 0xf;
		if(robo == end) return u;
		int mask = u >> 4;		
		for(int i = 0;i < sz; i++) if(mask & (1 << i)){
			for(int j : G[i]) if(~mask & (1<<j)){

				int v;
				v = clr(mask,i);
				v = set(v,j);
				v <<= 4;
				if(i == robo) v |= j;
				else v |= robo;				
				if(dist[v] == -1){
					Q.push(v);
					dist[v] = dist[u] + 1;
					note(v,u,i+1,j+1);
				}
			}
		} 
	}
	return 0;
}

void path(int v){
	int u =  prev[v][0];
	if(u == -1)  return;
	path(u);
	printf("%d %d\n",prev[v][1], prev[v][2]);
}

int main(){
	int T,n,m,start,end,status,t,i,u,v,cas=0;
	scanf("%d",&T);
	while(T--){

		scanf("%d %d %d %d",&n,&m,&start,&end);
		start--,end--;
		status = 1 << start;
		for(i=0;i<m;i++){
			scanf("%d",&t);
			status |= 1 << (t-1);
		}
		status <<= 4;
		status |= start;
		for(i=0;i<15;i++) G[i].clear();
		for(i=0;i<n-1;i++){
			scanf("%d %d",&u,&v);
			G[u-1].push_back(v-1);
			G[v-1].push_back(u-1);
		}
		//fprintf(stderr,"Case : %d\n",cas + 1);
		t = bfs(status,end,n);
		printf("Case %d: ",++cas);
		if(t){
			printf("%d\n",dist[t]);
			path(t);
		} else {
			puts("-1");
		}
		putchar('\n');
	}
	return 0;
}