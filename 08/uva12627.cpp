#include <cstdio>

long long f[32] = {1};

long long get(int row,int k){
	if(row == 0) return 0;
	if(row == (1<<k) ) return f[k];
	if(row <= (1<<(k-1))) return get(row, k-1) << 1;
	return (f[k-1] << 1) + get(row - (1 << (k-1)), k-1);
}

inline void init(){
	for(int i=1;i<31;i++) f[i] = f[i-1] * 3;
}

int main(){
	int T,i,r1,r2,k;
	scanf("%d",&T);
	init();
	for(i=0;i<T;i++){
		scanf("%d %d %d",&k,&r1,&r2);
		printf("Case %d: %lld\n",i+1,get(r2,k) - get(r1-1,k));
	}
	return 0;
}