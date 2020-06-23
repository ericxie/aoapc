#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 111

int dp[N][N];
char s[111];
const int inf = 0x3f3f3f3f;

inline bool match(int i,int j){
	return s[i]=='(' && s[j]==')' || s[i]=='[' && s[j]==']';
}

int dfs(int L,int R){
	if(dp[L][R] != inf) return dp[L][R];
	if(L>R) return dp[L][R] = 0;
	if(L==R) return dp[L][R] = 1;
	dp[L][R] = R - L + 1;
	for(int i=L;i<R;i++){
		if(match(i,R)) dp[L][R] = std::min(dp[L][R],dfs(L,i-1) + dfs(i+1,R-1));		
		dp[L][R] = std::min(dp[L][R],dfs(L,i) + dfs(i+1,R));
	}
	
	return dp[L][R];
}

void print(int L,int R){
	if(L==R) {
		if(s[L]=='(' || s[L] == ')') printf("()");
		else printf("[]");
	} else {
		if(match(L,R) && dp[L][R] == dp[L+1][R-1]) {
			printf("%c",s[L]);
			print(L+1,R-1);
			printf("%c",s[R]);
		} else {
			for(int i=L;i<R;i++) {
				if(dp[L][R] == dp[L][i] + dp[i+1][R]){				
					print(L,i);
					print(i+1,R);
					break;
				}
			}
		}
	}
}

int main(){
	int T,n;
	
	scanf("%d",&T);
	getchar();	
	while(T--){
		gets(s+1);
		gets(s+1);		
		n = strlen(s+1);
		if(n>0){
			memset(dp,0x3f,sizeof(dp));		
			dfs(1,n);
			print(1,n);	
		} 		
		putchar('\n');
		if(T) putchar('\n');
	}
	return 0;
}