#include <cstdio>
#include <vector>
#include <utility>

int main(){
	int k,y;
	while(~scanf("%d",&k)){
		std::vector<std::pair<int,int> > res;
		for(y=k+1;y<=k<<1;y++){
			if(y*k%(y - k)==0) res.emplace_back(y*k/(y-k),y);
		}
		printf("%lld\n",res.size());
		for(auto x : res){
			printf("1/%d = 1/%d + 1/%d\n",k,x.first,x.second);
		}
	}
	return 0;
}