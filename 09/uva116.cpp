#include <cstdio>
#include <algorithm>
const int inf = 0x3f3f3f3f;
int dp[111][111];
int n,m;

int main(){
	int i,j,k,cost;
	while(~scanf("%d %d",&n,&m)){
		for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",dp[i]+j);
		for(i=0;i<n;i++) dp[i][m] = 0;		
		
		for(j=m-1;j>=0;j--){
			for(i=0;i<n;i++){
				dp[i][j] += std::min(std::min(dp[i][j+1],dp[(i-1+n)%n][j+1]),dp[(i+1)%n][j+1]);
			}
		}
		for(i=k=0;i<n;i++) if(dp[i][0] < dp[k][0]) k = i;
		cost = dp[k][0];
		printf("%d",k+1);
		for(j=1;j<m;j++){
			int t[3] = {(k-1+n)%n,k,(k+1)%n};
			std::sort(t,t+3);
			for(k=t[0],i=1;i<3;i++) if(dp[t[i]][j] < dp[k][j]) k = t[i];
			printf(" %d",k+1);
		}
		printf("\n%d\n",cost);
	}
}