#include <string>
#include <map>
#include <cstdio>
#include <cstring>

struct cmp{
	bool operator()(const std::string &a,const std::string &b) const{
		if(a.size() == b.size()) return a < b;
		else return a.size() < b.size();
	}
};

std::multimap<std::string,int,cmp> ms;

void solve(){
	int cnt=0;
	for(auto &x : ms){
		std::string prefix = x.first.substr(0,x.first.size()-1);
		if(x.first == "") cnt++;
		if(cnt>1 || ms.count(prefix) != 1 || ms.count(x.first) != 1){
			puts("not complete");
			return;
		}
	}
	auto it = ms.begin();
	printf("%d",it->second);
	while(it++,it != ms.end()){
		printf(" %d",it->second);	
	}
	putchar('\n');
}


int main(){
	char s[333];
	while(scanf("%s",s)!=EOF){
		int id,t;
		char path[333];
		t = sscanf(s,"(%d,%[LR])",&id,path);
		if(t==2) {
			ms.emplace(std::string(path),id);
		} else if(t==1){
			ms.emplace(std::string(""),id);
		} else {
			solve();
			ms.clear();
		}	
	}
	return 0;
}