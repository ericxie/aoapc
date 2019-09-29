#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct node{
	std::string id;
	std::string s;	
	bool tag;
	bool operator<(const node &x)const {
		if(id < x.id) return true;
		else if(id == x.id && s < x.s) return true;
		return false;
	} 
	bool operator==(const node &x)const {
		return id == x.id;
	}
	
	node(const std::string &x){
		tag = false;
		id = s = x;
		std::transform(id.begin(),id.end(),id.begin(),::tolower);
		std::sort(id.begin(),id.end());
	}
};

bool cmp(const node &x,const node &y){
	if(x.tag == y.tag) return x.s < y.s;
	else return x.tag < y.tag; 
}

int main(){
	std::string s,id;
	std::ios::sync_with_stdio(false);
	std::vector<node> vn;
	
	while(std::cin >> s, s!="#") vn.emplace_back(s);	
	std::sort(vn.begin(),vn.end());
	auto p = vn.begin() ,q = p+1;
	while(p!=vn.end()){
		while(q!=vn.end() && *p==*q){
			p->tag = true;
			q->tag = true;
			q++;
		}
		p = q++;	
	}	
	std::sort(vn.begin(),vn.end(),cmp); 	

	for(auto t : vn){
		if(!t.tag) std::cout << t.s << '\n';
		else break;
	}
	return 0;
}

