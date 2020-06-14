#include <cstdio>
#include <queue>
#include <cstring>
#include <tuple>

const int inf = 0x3f3f3f3f;
int dp[33][3];
int block[33][3]={inf,inf,inf};

int solve(int n){
	int i,j,ans;
	int p[3][2]={{1,2},{0,2},{0,1}};
	std::priority_queue<std::tuple<int,int,int> > pq;
	memset(dp,0,sizeof(dp));
	pq.emplace(0,0,0);
	pq.emplace(0,0,1);
	pq.emplace(0,0,2);

	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();		
		int h = std::get<0>(x);
		int a = std::get<1>(x);
		int b = std::get<2>(x);
		if(h < dp[a][b]) continue;
		for(i=1;i<=n;i++) for(j=0;j<3;j++) {
			int dl = block[a][p[b][0]];
			int dw = block[a][p[b][1]];
			int ul = block[i][p[j][0]];
			int uw = block[i][p[j][1]];
			if( (dl > ul && dw > uw) || 
				(dl > uw && dw > ul)){
				if(dp[a][b] + block[i][j] > dp[i][j]){
					dp[i][j] = dp[a][b] + block[i][j];
					pq.emplace(dp[i][j],i,j);
				}
			}
		}
	}
	ans = 0;
	for(i=1;i<=n;i++) for(j=0;j<3;j++) if(ans < dp[i][j]) ans = dp[i][j];
	return ans;
}

int main(){
	int n,i,j,k=0;
	while(scanf("%d",&n),n){
		for(i=1;i<=n;i++) for(j=0;j<3;j++) scanf("%d",block[i]+j);
		printf("Case %d: maximum height = %d\n",++k,solve(n));
	}
	return 0;
}