#include <cstdio>
#include <queue>

int main(){
	int i,n,t;
	std::priority_queue<long long> a;
	while(scanf("%d",&n),n){
		for(i=0;i<n;i++){
			scanf("%d",&t);
			a.push(-t);
		}
		long long ans = 0;
		while(a.size() > 1){
			auto x = a.top(); a.pop();
			auto y = a.top(); a.pop();
			ans += -(x + y);
			a.push(x+y);
		}
		a.pop();
		printf("%lld\n",ans);
	}
	return 0;
}