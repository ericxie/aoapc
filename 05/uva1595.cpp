#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

std::vector<std::pair<int,int> > points;

std::pair<bool,int> get(std::vector<std::pair<int,int> >::iterator left,std::vector<std::pair<int,int> >::iterator right){
	--right;
	int cx = (left->second + right->second)>>1 , x;
	while(left <= right){
		x = (left->second + right->second)>>1;
		if(x != cx) return std::make_pair(false,cx);
		++left,--right;
	} 
	return std::make_pair(true,cx);
}

int main(){
	int T,n,x,y;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		points.clear();
		while(n--){
			scanf("%d %d",&x,&y);
			points.emplace_back(y,x<<1);
		}
		std::sort(points.begin(),points.end());
		bool flag = true;
		int cx;
		for(auto it = points.begin(); it != points.end();){
			auto last  = it+1;
			for(; last != points.end() && last->first == it->first; ++last);
			auto ret = get(it,last);
			if(flag) cx = ret.second, flag = false;
			if(!ret.first || cx != ret.second){
				puts("No");
				goto next_case;
			} 
			it = last;
		}
		puts("Yes");
		next_case: ;
	}	
}