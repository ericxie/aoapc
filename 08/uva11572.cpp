#include <cstdio>
#include <unordered_map>
#include <vector>

int main(){
	int T,n,i,left,ans,len;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		std::vector<int> a(n);
		std::unordered_map<int,int> pos;
		for(i=0;i<n;i++) scanf("%d",&a[i]);

		for(ans = left = i = 0; i<n; i++){
			auto it = pos.find(a[i]);
			if(it == pos.end()) pos.emplace(a[i],i);
			else{
				if(it->second < left){
					it->second = i;
				} else {
					len = i - left;
					if(len > ans) ans = len;
					left = it->second + 1;
					it->second = i;
				}				
			}
		}
		len = i - left;
		if(len > ans) ans = len;
		printf("%d\n",ans);
	}
	return 0;
}