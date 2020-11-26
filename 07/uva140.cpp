#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <regex>
#include <set>
#include <vector>

std::vector<int> G[26];
std::set<int> sigma;

void parse(std::string &buf){	
	std::regex edge("([A-Z]):([A-Z]*)");
	std::smatch sm;
	memset(G,0,sizeof(G));
	sigma.clear();
	while(regex_search(buf, sm, edge))
    {
    	size_t i,p,q;
    	p = sm[1].str()[0] - 'A';
    	sigma.insert(p);
    	std::string s = sm[2].str();
    	for(i=0;i < s.size();i++){
    		q = s[i] - 'A';
    		sigma.insert(q);
    		G[p].push_back(q);
    		G[q].push_back(p);
    		//std::cout << char('A'+ p) << " - " << char('A'+q) << '\n';
    	}
        buf = sm.suffix();
    }
}

int bandwidth(std::vector<int> &a){
	int i,n = a.size(),res = 1;
	int pos[26];
	for(i=0;i<n;i++) pos[a[i]] = i;
	for(i=0;i<n;i++){
		for(auto x : G[a[i]]){
			res = std::max(res,abs(pos[x] - i));
		}
	}
	return res;
}

void out(std::vector<int> &a,int bw){
	for(auto x : a) std::cout << char('A' + x) << ' ';
	std::cout << "-> " << bw << '\n';
}

int main(){
	std::string buf;
	
	while((std::cin >> buf), buf[0]!='#') {
		parse(buf);
		std::vector<int> a(sigma.begin(),sigma.end());
		int ans;	
		std::vector<int> va;	
		ans = a.size();
		do{			
			int r = bandwidth(a);			
			if(ans > r){
				ans = r;
				va = a;
			}
		}while(std::next_permutation(a.begin(),a.end()));
		out(va,ans);
	}
	return 0;
}

