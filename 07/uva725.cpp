#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>

int main(){
	std::vector<int> a;
	std::set<std::pair<int,int> > result[80];
	int n,m,r,flag = 0;
		
	for(int i=0;i<10;i++) a.push_back(i);
	
	do{
		n = 10000 * a[0] + 1000 * a[1] + 100 * a[2] + 10 * a[3] + a[4];
		m = 10000 * a[5] + 1000 * a[6] + 100 * a[7] + 10 * a[8] + a[9];
		r = n / m;
		if(r*m == n) result[r].emplace(n,m);
	}while(std::next_permutation(a.begin(),a.end()));
	
	while(scanf("%d",&n),n){
		if(flag) putchar('\n');
		flag = 1;
		if(result[n].empty()){
			printf("There are no solutions for %d.\n",n);
		} else {
			for(auto x : result[n]){
				printf("%05d / %05d = %d\n", x.first, x.second, n);
			}
		}
	}

	return 0;
}