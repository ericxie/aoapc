#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5;
int a[N],left[N],right[N],dp[N];

int main(){
	int T,n,i,ans;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(i = 0; i<n;i++) scanf("%d",a+i);
		left[0] = 1;
		for(i = 1; i<n;i++) {
			if(a[i]>a[i-1]) left[i] = left[i-1] + 1;
			else left[i] = 1;
		}
		right[n-1] = 1;
		for(i=n-2;i>=0;i--){
			if(a[i]<a[i+1]) right[i] = right[i+1] + 1;
			else right[i] = 1;
		}
		// fprintf(stderr,"left : ");
		// for(int j = 0;j <n;j++) fprintf(stderr,"%d,",left[j]);
		// fprintf(stderr,"\n");

		// fprintf(stderr,"right: ");
		// for(int j = 0;j <n;j++) fprintf(stderr,"%d,",right[j]);
		// fprintf(stderr,"\n");
		
		dp[0] = a[0];
		ans = left[0] + right[0] - 1;
		int sz = 1,len;
		for(i=1;i<n;i++) {
			if(a[i] > dp[sz - 1]){
				len = sz + right[i];
			} else {
				auto it = std::lower_bound(dp,dp+sz,a[i]);
				len = std::distance(dp,it) + right[i];	
			}
			if(len > ans) ans = len;
			//fprintf(stderr,"%d : %d %d\n",i,len,ans);
			if(left[i] > sz) dp[sz++] = a[i];
			else if(a[i] < dp[left[i]-1])  dp[left[i]-1] = a[i];						
						
			//for(int j = 0 ; j<sz; j++) fprintf(stderr,"%d,",dp[j]);
			//fprintf(stderr,"\n");
		}
		
		printf("%d\n",ans);
	}
	return 0;
}