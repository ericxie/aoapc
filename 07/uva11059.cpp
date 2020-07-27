#include <cstdio>
#include <algorithm>
typedef long long LL;

inline LL mul(int *a,int L,int R){
	LL ans = L <= R;
	for(int i=L;i<=R;i++) ans *= a[i];
	return ans;
}

LL dfs(int *a,int L,int R){
	int i,first=R+1,last=L-1,cnt=0;
	LL ans;
	for(i=L;i<=R;i++) cnt += a[i] < 0;
	for(i=L;i<=R&&a[i]>0;i++);
	first = i; 
	for(i=R;i>=L&&a[i]>0;i--);
	last = i;

	if(~cnt & 1){
		ans = mul(a,L,R);
	} else {
		LL t1,t2,t3;
		
		t1 = mul(a,L,first - 1);
		t3 = mul(a,last+1,R);
		if(first == last) ans = std::max(t1,t3);
		else {
			t2 = mul(a,first+1,last -1);		
			if(L==first) t1 = 1;
			if(R==last) t3 = 1;
			ans = std::max(t1*a[first]*t2,t2*a[last]*t3);
		}
	}
	return ans;
}

int main(){
	int i,n,a[22],L,R,k=0;
	LL ans,t;
	while(~scanf("%d",&n)){
		ans = 0;
		for(i=0,L=0,R=0;i<n;i++) {
			scanf("%d",a+i);
			if(a[i] == 0) {
				t = dfs(a,L,i-1); 
				if(t > ans) ans = t;
				L = R = i+1;
			} else {
				R = i;
			}
		}
		if(L< n){
			t = dfs(a,L,R);
			if(t > ans ) ans = t;
		}
		printf("Case #%d: The maximum product is %lld.\n\n",++k,ans);
	}
	return 0;
}