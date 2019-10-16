#include <cstdio>
#include <cstdlib>
const int N = 22;

int ducci(int *a,int n){
	int i,t;
	bool flag = true;
	a[n] = a[0];
	for(i=0;i<n;i++){
		a[i] = abs(a[i] - a[i+1]);
		if(a[i]) flag = false;
	}
	return flag;
}

void solve(int *a,int n){
	int cnt = 0;
	while(!ducci(a,n) && cnt++ < 1000) ;
	puts(cnt>1000?"LOOP":"ZERO");
}

int main(){
	int T,a[N],n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",a+i);
		solve(a,n);
	}
	return 0;
}