#include <cstdio>

int solve(int d,int x){
	int res = 1 << d;
	while(d--){
		res |= (x&1) << d;
		x >>= 1;
	}
	return res;
}

int main(){
	int n,d,x;
	scanf("%d",&n);
	while(n--){
		scanf("%d %d",&d,&x);
		printf("%d\n",solve(d-1,x-1));
	}
	return 0;
}