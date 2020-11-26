#include <cstdio>
#include <algorithm>

const int N = 18;
int a[N];

int dfs(int maxd,int d,int n,int h){
	int i;	
	//fprintf(stderr,"%d %d : %d\n",maxd,d,a[d]);
	if(a[d] == n) return 1;
	if(d == maxd) return 0;	
	if((h << (maxd - d)) < n) return 0;

 	for(i=0;i<=d;i++) {
		a[d+1] = a[d] + a[i];
		if(dfs(maxd,d+1,n,a[d+1])) return 1;
		if(a[d] > a[i]){
			a[d+1] = a[d] - a[i];
			if(dfs(maxd,d+1,n,h)) return 1;
		}
	}
	return 0;
}

int ida(int n){
	int i;

	a[0] = 1;
	for(i=0;i<N;i++) {
		if(dfs(i,0,n,1)) return i;
	}
	return -1;
}


int main(){
	int n;
	
	while(scanf("%d",&n),n){
		//fprintf(stderr,"%d : \n", n);
		printf("%d\n",ida(n));
	}
	return 0;
}
