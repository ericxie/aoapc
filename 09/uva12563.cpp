#include <cstdio>
#include <algorithm>
#include <cstring>
int dp[55*60*3];
int song[55]; 

int main(){
	int T,n,L,i,j,k=0,len,cnt;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&L);

		for(i=len=0;i<n;i++) scanf("%d",song+i),len+=song[i];
		if(L > len){
			printf("Case %d: %d %d\n",++k,n+1,len+678);
		} else {
			for(i=1;i<L;i++) dp[i] = -100;
			dp[0] = 0;
			for(i=0;i<n;i++)
				for(j=L-1;j>=song[i];j--) 
					dp[j] = std::max(dp[j],dp[j-song[i]]+1);
			cnt = len = 0;
			for(j=L-1;j>0;j--) if(dp[j]>=0){
				if(dp[j] > cnt){
					cnt = dp[j];
					len = j;
				}
			}			
			printf("Case %d: %d %d\n",++k,cnt + 1,len + 678);	
		}
		

	}
	return 0;
}