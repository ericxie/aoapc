#include <cstdio>
#include <cstring>
#define N 55
const int inf = 1e9;

int main(){
	int n,i,j,k,L,len,a[N],dp[N][N];
	while(scanf("%d",&L),L){
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d",a+i);
		a[n+1] = L;
		memset(dp,0,sizeof(dp));
		for(len=2;len <= n+1; len++){
			for(i=0 ; i + len <= n + 1; i++){
				j = i + len;
				dp[i][j] = inf;
				for(k=i+1;k<j;k++) if(dp[i][k] + dp[k][j] + a[j] - a[i] < dp[i][j]){
					dp[i][j] = dp[i][k] + dp[k][j] + a[j] - a[i];
				}
			}
		}
		printf("The minimum cutting is %d.\n",dp[0][n+1]);
	}
	return 0;
}