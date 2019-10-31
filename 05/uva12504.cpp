#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <sstream>
#include <map>
#include <vector>

std::map<std::string,std::string> before,after;
std::vector<std::string> add;
std::vector<std::string> del;
std::vector<std::string> update;


void parse(std::string &buf, std::map<std::string,std::string> &dict){
	std::regex re("([a-z]+):([0-9]+)");
	std::smatch sm;
	dict.clear();
	while(std::regex_search(buf,sm,re)){
		dict.emplace(sm[1].str(),sm[2].str());
		buf = sm.suffix();	
	} 
}

void out(const std::vector<std::string> &vs, char c){
	for(auto x : vs){
		std::cout << c << x;
		c = ',';
	}
	std::cout << '\n';
}

void solve(){
	auto itb = before.begin();
	auto ita = after.begin();
	add.clear();
	del.clear();
	update.clear();

	while(itb != before.end() && ita != after.end()){
		if(itb->first == ita->first){
			if(itb->second != ita->second) update.push_back(itb->first);
			++itb,++ita;
		} else if(itb->first < ita->first) {
			del.push_back(itb->first);
			++itb;
		} else {
			add.push_back(ita->first);
			++ita;
		}
	}
	for(; itb != before.end(); ++itb) del.push_back(itb->first);
	for(; ita != after.end(); ++ita) add.push_back(ita->first);	
		
	if(add.size()) out(add,'+');
	if(del.size()) out(del,'-');
	if(update.size()) out(update,'*');
	if(add.size() == 0 && del.size() == 0  && update.size() == 0) std::cout << "No changes\n";
	std::cout << '\n';
}

int main(){
	std::string buf;
	int n;
	std::getline(std::cin,buf);
	std::stringstream ss(buf);
	ss >> n;
	while(n--){
		std::getline(std::cin,buf);
		parse(buf,before);
		std::getline(std::cin,buf);
		parse(buf,after);
		solve();	
	}
	return 0;
}