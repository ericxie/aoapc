#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 5005

struct node{
	int left[2],right[2];
	inline void init(){ left[0] = left[1] = N+1; right[0]=right[1]=-1; }
	inline bool in(int i,int j){
		return (left[0] <= i || left[1] <=j) && (i < right[0] || j < right[1]) ;
	}
}ch[26];

int dp[N][N];

void get(char *s,int k){
	char *p;
	for(p=s;*p;p++){
		if(ch[*p-'A'].left[k] == N+1) ch[*p-'A'].left[k] = p-s+1;
	}
	for(p--;p>=s;p--){
		if(ch[*p-'A'].right[k] == -1) ch[*p-'A'].right[k] = p-s+1;
	}
}

int solve(int n,int m){
	int i,j,k;
	for(i=0;i<=n;i++) for(j=0;j<=m;j++){
		dp[i][j] = 0;
		for(k=0;k<26;k++) dp[i][j] += ch[k].in(i,j);
	}
	for(i=1;i<=n;i++) dp[i][0] += dp[i-1][0];
	for(j=1;j<=m;j++) dp[0][j] += dp[0][j-1];
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			dp[i][j] += std::min(dp[i-1][j] ,dp[i][j-1] ) ;
	return dp[n][m];
}

int main(){
	int n,m,T;
	char a[N],b[N];
	scanf("%d",&T);
	while(T--){
		for(int i=0;i<26;i++) ch[i].init();
		scanf("%s %s",a+1,b+1);
		n = strlen(a+1);
		m = strlen(b+1);
		get(a+1,0);
		get(b+1,1);		
		printf("%d\n",solve(n,m));
		
	}
	return 0;
}