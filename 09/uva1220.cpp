#include <iostream>
#include <vector>
#include <string>

#define N 222
struct node{
	std::string name;
	int sum[2];
	bool tag[2];
	std::vector<int> sons;
	node() = default;
	node(std::string &s){
		name = s;
		sum[0] = 0;
		sum[1] = 1;
		tag[0] = tag[1] = false;
		sons.clear();
	}	
}emp[N];

int find(std::string &s,int n){
	int i;
	for(i=0;i<n && s != emp[i].name;i++);
	return i; 
}

void read(int n){
	std::string s,t;
	int k,i,j,c;
	std::cin >> s;
	emp[0] = node(s);
	
	for(k=1,c=1;c<n;c++){
		std::cin >> s >> t;
		i = find(s,k);
		if(i==k) emp[k++] = node(s);
		j = find(t,k);
		if(j==k) emp[k++] = node(t);		
		emp[j].sons.push_back(i);
	}
}

void dfs(int p){
	auto &u = emp[p];
	if(u.sons.size() > 0){
		for(auto x : u.sons){
			dfs(x);
			const auto &v = emp[x];
			bool d = v.sum[0]<v.sum[1];			
			u.sum[0] += v.sum[d];
			u.tag[0] = u.tag[0] || v.tag[d];
			if(v.sum[0] == v.sum[1]) u.tag[0] = true;
			u.sum[1] += emp[x].sum[0];
			u.tag[1] = u.tag[1] || v.tag[0];
		}
	}
}

int main(){
	int n;
	std::ios::sync_with_stdio(false);
	while(std::cin >> n,n){
		read(n);
		dfs(0);
		auto &u = emp[0];
		bool d = u.sum[0] < u.sum[1];
		std::cout << u.sum[d];
		if(u.sum[0] == u.sum[1] || u.tag[d] ) std::cout << " No\n";
		else std::cout << " Yes\n";		
	}
	return 0;
}

