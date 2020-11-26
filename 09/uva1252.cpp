#include <cstdio>
#include <algorithm>

const int N = 128;
const int M = 11;

int n,m;
int dp[1<<M][1<<M];
int cnt[1<<M][1<<M];
int dfs(int s,int t){	
	int i;
	if(dp[s][t] != M+1) return dp[s][t];
	if(cnt[s][t] == 0 || cnt[s][t] == 1) return dp[s][t] = 0;
	for(i=0;i<m;i++){
		if()
	}
}


int main(){
	int i,j;
	char a[N][M+1];
	while(scanf("%d %d",&m,&n),m!=0){		
		for(i=0;i<n;i++){
			scanf("%s",a[i]);
		}
				
	}
	return 0;
}