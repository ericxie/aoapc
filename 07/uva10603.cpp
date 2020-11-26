#include <cstdio>
#include <map>
#include <queue>
#include <cstring>

const int N = 201*201;
const int inf = 0x3f3f3f3f;

int vis[N];
int dist[N];
std::map<int,int> G[N];

inline void addEdge(int u,int v,int w){
	auto it = G[u].find(v);
	if(it == G[u].end()) G[u].emplace(v,w);
	else if(it->second > w) it->second = w; 
}

inline int idx(int i,int j){ return i*201 + j; }

void build(int a,int b,int c){
	int i,j,k,u;

	for(i=0;i<N;i++) G[i].clear();
	for(i=0;i<=a;i++) for(j=0;j<=b;j++){
		k = c - i - j;
		if(k<0) break;
		u = idx(i,j);
		if(i){
			if(i+j<=b) addEdge(u,idx(0,i+j),i) ;	// i->j , not overflow
			else addEdge(u,idx(i+j-b,b),b-j);		// i->j , overflow
			if(i+k<=c) addEdge(u,idx(0,j),i);		// i->k
			else addEdge(u,idx(i+k-c,j),c-k);
		}
		if(j){
			if(i+j<=a) addEdge(u,idx(i+j,0),j) ;	// j->i
			else addEdge(u,idx(a,i+j-a),a-i);	
			if(j+k<=c) addEdge(u,idx(i,0),j);		// j->k
			else addEdge(u,idx(i,j+k-c),c-k);
		}
		if(k){
			if(i+k<=a) addEdge(u,idx(i+k,j),k);		// k->i
			else addEdge(u,idx(a,j),a-i);
			if(j+k<=b) addEdge(u,idx(i,j+k),k);		// k->j
			else addEdge(u,idx(i,b),b-j);
		}
	}
}

void dijkstra(){
	
	memset(vis,0,sizeof(vis));
	memset(dist,0x3f,sizeof(dist));
	dist[0] = 0;
	std::priority_queue<std::pair<int,int> > pq;
	pq.emplace(0,idx(0,0));
	
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		int s =  - x.first;
		int u = x.second; 
		
		if(vis[u]) continue;
		vis[u] = 1;
		
		for(auto y : G[u]) {
			int v = y.first;
			int w = y.second;
			if(w + s < dist[v]){
				dist[v] = w + s;
				pq.emplace(-dist[v],v);
			}
		}
	}
}

inline int near(int a,int b,int c,int d){
	int res = inf;
	if(a <= d) res = d - a;
	if(b <= d && d - b < res) res = d - b;
	if(c <= d && d - c < res) res = d - c;
	return res;   
}

int main(){
	int T,i,j,k,u,a,b,c,d;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d",&a,&b,&c,&d);
		build(a,b,c);
		dijkstra();
		int ans=inf,delta=inf;
		for(i=0;i<=a;i++) for(j=0;j<=b;j++){
			k = c - i - j;
			if(k < 0) break;
			u = idx(i,j);
			if(dist[u] == inf) continue;
			int m = near(i,j,k,d);
			if(m < delta || m == delta && dist[u] < ans){
				delta = m;
				ans = dist[u];
			} 
			//fprintf(stderr,"%d %d %d : %d , %d , %d , %d\n",i,j,k,dist[u],m,delta, ans);
		}
		printf("%d %d\n",ans,d - delta);
	}
	return 0;
}


