#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define N 1011
int pal[N][N];
int dp[N];
char a[N];

void proc(int i,int n){
	int l = i-1, r = i+1;
	pal[i][i] = 1;
	while(l>0 && r <= n){
		if(a[l] == a[r]) pal[l][r] = 1;
		else break;
		l--,r++;
	}
	l = i, r = i+1;
	while(l>0 && r <= n){
		if(a[l] == a[r]) pal[l][r] = 1;
		else break;
		l--,r++;
	}
}

int main(){
	int T,i,j,n;
	
	scanf("%d",&T);
	while(T--){
		scanf("%s",a+1);
		n = strlen(a+1);
		memset(pal,0,sizeof(pal));
		for(i=1;i<=n;i++) proc(i,n);
		memset(dp,0,sizeof(dp));
		dp[0] = 0;
		for(i=1;i<=n;i++) {
			dp[i] = i+1;
			for(j=1;j<=i;j++) if(pal[j][i]) dp[i] = std::min(dp[i],dp[j-1] + 1);
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
