#include <cstdio>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
struct Lamp{
	int v,k,c,l;
	Lamp() = default;
	Lamp(int v,int k,int c,int l) :v(v),k(k),c(c),l(l){}
	inline bool operator<(const Lamp &rhs) const{
		return v < rhs.v;
	}
};

Lamp lamps[1011];
int cnt[1011];
int dp[1011];

int main(){
	int i,j,n,v,k,c,l;
	while(scanf("%d",&n),n){		
		for(i=1;i<=n;i++){
			scanf("%d %d %d %d",&v,&k,&c,&l);
			lamps[i] = Lamp(v,k,c,l);
		}
		std::sort(lamps+1,lamps + n + 1);		
		for(i=1;i<=n;i++) cnt[i] = cnt[i-1] + lamps[i].l;		
		for(i=1;i<=n;i++){			
			dp[i] = cnt[i] * lamps[i].c + lamps[i].k;
			for(j=1;j<i;j++) 
				dp[i] = std::min( dp[j] + (cnt[i] - cnt[j]) * lamps[i].c + lamps[i].k , 
					              dp[i]);			
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}