#include <cstdio>
#include <stack>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

typedef std::list<int> Set;
std::map<Set,int> IDPool;
std::vector<Set> SetPool;

int getID(Set x){
	if(IDPool.count(x)) return IDPool[x];
	SetPool.push_back(x);
	return IDPool[x] = SetPool.size() - 1;
 }

 void out(){
 	puts("++++++++++++++++++++++++++++");
 	for(auto i : SetPool){
 		for(auto j : i){
 			printf("%d,",j);
 		}
 		putchar('\n');
 	}
 	puts("----------------------------"); 
 }

 void solve(int n){
 	char buf[11];
	std::stack<int> s;
	while(n--){
		scanf("%s",buf);
		//puts(buf);
		if(buf[0] == 'P') s.push(getID(Set())); 
		else if(buf[0] == 'D') s.push(s.top()); 
		else {
			Set x1 = SetPool[s.top()];
			s.pop();
			Set x2 = SetPool[s.top()];
			s.pop();
			Set dest;
			if(buf[0] == 'U')	std::set_union(x1.begin(),x1.end(),x2.begin(),x2.end(),std::back_inserter(dest));
			else if(buf[0] == 'I') std::set_intersection(x1.begin(),x1.end(),x2.begin(),x2.end(),std::back_inserter(dest));
			else{
				dest = x2;
				int id = getID(x1);
				auto it = dest.begin();
				while(it != dest.end() && *it < id) ++it;				
				if(it == dest.end() || *it != id) dest.insert(it,id);				
			}			
			s.push(getID(dest));
		}	
		//out();
		printf("%lld\n",SetPool[s.top()].size());	
	}
 }

int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		solve(n);
		if(T) puts("***");
	} 
	return 0;
}
