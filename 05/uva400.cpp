#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> files;
const int W = 60;

void solve(int n,int w){
	int col,row,i,j,k;
	for(i=0;i<W;i++) std::cout << '-';
	std::cout << '\n';
	col = (W+2) / (w + 2);
	row = (n + col - 1)  / col;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			k = j * row  + i;
			if(k>=n) continue;
			std::cout << std::setw(w) << std::left << files[k];
			if(j == col -1 || k + row >=n ) std::cout << '\n';
			else std::cout << "  ";
		} 
	}
}

int main(){
	std::string s;
	std::ios::sync_with_stdio(false);
	int n,w;
	while(std::cin >> n){
		files.resize(n);
		w = 0;
		for(int i=0;i<n;i++){
			std::cin >> files[i];
			if(w < files[i].size()) w = files[i].size();
		}
		std::sort(files.begin(),files.end());
		solve(n,w);
	}
	return 0;
}
