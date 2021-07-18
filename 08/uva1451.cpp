#include <cstdio>
#include <vector>
#include <pair>
const int N = 100011;
char s[N];
int sum[N],pos[N];

inline bool cmp(int l1,int l2,int r){
	return (sum[r] - sum[l1-1]) * (r - l2 + 1) < (sum[r] - sum[l2-1]) * (r - l1 + 1);
}

int main(){
	int T,n,m,i,k,t;

	scanf("%d",&T);
	while(T--){
		scanf("%d %d ",&n,&m);
		gets(s);
		sum[0] = 0;
		for(i=0;i<n;i++) sum[i+1] = sum[i] + s[i] - '0';
		 		
	}
	return 0;
}