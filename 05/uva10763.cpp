#include <map>
#include <utility>
#include <algorithm>
#include <cstdio>

int main(){
	int n,a,b;
	while(scanf("%d",&n),n){
		std::map<std::pair<int,int>,int> s;
		while(n--){
			scanf("%d %d",&a,&b);
			if(a>b) std::swap(a,b);
			auto pii = std::make_pair(a,b);
			if(s.count(pii) == 0) s[pii] = 1;
			else s[pii]^=1;
		}
		for(auto &x : s) if(x.second){
			puts("NO");
			goto next;
		}
		puts("YES");
		next: ;
	}
	return 0;
}