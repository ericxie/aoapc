#include <iostream>
#include <string>

const int N = 8;

int pos[N];

inline char solve(std::string &s, std::string &t){
	size_t i,j;
	for(i=0,j=1;i<t.size();i++){
		j = j << 1 | (t[pos[i]] == '1');
	}
	j -= s.size();
	return s[j];
}

int main(){
	int i,n,m,k=0;
	std::string x,s,t;
	while(std::cin >> n, n){
		for(i=0; i<n; i++){
			std::cin >> x;
			pos[i] = x[1] - '1';
		}
		std::cin >> s;
		std::cin >> m;
		std::cout << "S-Tree #" << ++k << ":\n";
		for(i=0;i<m;i++){
			std::cin >> t;			
			std::cout << solve(s,t);
		}
		std::cout << "\n\n";
	}
}