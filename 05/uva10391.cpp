#include <iostream>
#include <string>
#include <set>


int main(){
	std::ios::sync_with_stdio(false);
	std::string buf;
	std::set<std::string> ss;
	while(std::getline(std::cin,buf)){
		auto it = ss.begin();
		ss.emplace_hint(it,buf);
		it = ss.end();
	}
	for(auto &x : ss){
		size_t m = x.size();
		for(size_t i=1;i<m;i++){
			std::string prefix = x.substr(0,i);
			std::string suffix = x.substr(i,m-i);
			if(ss.find(prefix)!=ss.end() && 
			   ss.find(suffix)!=ss.end()){
				std::cout << x << '\n';
				break;
			}				
		}
	}
	return 0;
}