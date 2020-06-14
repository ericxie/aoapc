#include <cstdio>
#include <queue>
#include <tuple>
#include <cstring>

int train[222][55];
int dp[222][55];
int run[55];
int N,T;

const int INF = 0x3f3f3f3f;

void bfs(std::tuple<int,int,int> s){
	std::priority_queue<std::tuple<int,int,int> > pq;
	pq.push(s);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		int v =  - std::get<0>(x);
		int t =  std::get<1>(x);
		int p =  std::get<2>(x);
		//fprintf(stderr,"%d %d : %d\n",t,p,v);
		if(t==T && p==N) return;
		if(v > dp[t][p]) continue;
		if(dp[t+1][p] > dp[t][p] + 1) {
			dp[t+1][p] = dp[t][p] + 1;
			pq.push(std::make_tuple(-dp[t+1][p],t+1,p));
		}
		if(p < N && (train[t][p] & 1) && t + run[p] <= T && dp[t+run[p]][p+1] > dp[t][p]) {
			dp[t+run[p]][p+1] = dp[t][p];
			pq.push(std::make_tuple(-dp[t][p],t+run[p],p+1));
		}
		if(p > 1 && (train[t][p] & 2) && t + run[p-1] <= T && dp[t+run[p-1]][p-1] > dp[t][p]) {
			dp[t+run[p-1]][p-1] = dp[t][p];
			pq.push(std::make_tuple(-dp[t][p],t+run[p-1],p-1));
		}
	}	
}

void solve(){
	memset(dp,0x3f,sizeof(dp));
	dp[0][1] = 0;
	bfs(std::make_tuple(0,0,1));
	if(dp[T][N] >= INF) puts("impossible");
	else printf("%d\n",dp[T][N]);
}

int main(){
	int k = 0,i,j,n,s;
	while(scanf("%d",&N),N){
		scanf("%d",&T);
		for(i=1;i<N;i++) scanf("%d",run+i);
		memset(train,0,sizeof(train));
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%d",&s);
			train[s][1] |= 1;
			for(j=1;j<N;j++) {
				s += run[j];
				if(s > T) break;
				train[s][j+1] |= 1;
			}
		}
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%d",&s);
			train[s][N] |= 2;
			for(j=1;j<N;j++) {
				s += run[N-j];
				if(s > T) break;
				train[s][N-j] |= 2;
			}
		}
		// for(i=0;i<=T;i++) {
		// 	fprintf(stderr,"%3d:",i);
		// 	for(j=1;j<=N;j++) fprintf(stderr,"%2d",train[i][j]);
		// 	fprintf(stderr,"\n");
		// }
		printf("Case Number %d: ",++k);
		solve();
	}
	return 0;
}