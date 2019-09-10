#include <cstdio>
#include <algorithm>
int get(int x){
	int s = x;
	while(x){
		s += x % 10;
		x /= 10;
	}
	return s;
}

int main(){
	int T,n,i;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(i=std::max(n-45,1); i<n; i++){
			if(get(i) == n){
				printf("%d\n",i);
				break;
			}
		}
		if(i==n) puts("0");
	}
	return 0;
}