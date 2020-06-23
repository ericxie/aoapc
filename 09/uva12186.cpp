#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>

#define N 100005

struct node{
	int cost;
	int parent;
	std::list<int> sons;
	void clear(){
		cost = 0;
		parent = -1;
		sons.clear();
	}
}emp[N];

void read(int n){
	int i,p;
	for(i=0;i<=n;i++) emp[i].clear();
	for(i=1;i<=n;i++){
		scanf("%d",&p);
		emp[i].parent = p;
		emp[p].sons.push_back(i);
	}
}

int dfs(int no,int T){
	auto &u = emp[no];
	auto n = u.sons.size();
	int m = (n * T + 99) / 100;
	if(n == 0) {
		return u.cost = 1; 
	} else {
		std::vector<int> vi;
		for(auto x : u.sons) vi.push_back(dfs(x,T));
		std::sort(vi.begin(),vi.end());
		for(int i = 0; i < m; i++) u.cost += vi[i];
		return u.cost;
	}
}

int main(){
	int n,T;
	while(scanf("%d %d",&n,&T),n!=0){
		read(n);
		printf("%d\n",dfs(0,T));
	}
	return 0;
}