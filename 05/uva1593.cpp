#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
const int N = 1000;
const int M = 200;


std::vector<std::string > pool;
std::vector<int > mat[N];
int width[M];

int main(){
	std::string buf;
	int row=0,col,len,cnt=0;
	while(std::getline(std::cin,buf)){
		std::stringstream ss(buf);
		col=0;
		while(ss >> buf){
			pool.push_back(buf);
			mat[row].push_back(cnt++);
			len = buf.size();
			if(len > width[col]) width[col] = len;
			col++;
		}
		row++;
	}
	for(int i=0;i<row;i++){
		int m = mat[i].size();
		for(int j=0;j<m;j++){
			//std::cout << j;
			std::cout << std::left <<std::setw(j<m-1?width[j]+1:0) << pool[mat[i][j]];			
		}
		std::cout << '\n';
	}
	return 0;
}