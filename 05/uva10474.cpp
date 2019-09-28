#include <cstdio>
#include <vector>
#include <algorithm>

int main(){
	int n,m,i,T=0;
	while(scanf("%d %d",&n,&m),n){
		int a[n],t;
		for(i=0;i<n;i++) scanf("%d",a+i);
		std::sort(a,a+n);
		printf("CASE# %d:\n",++T);
		for(i=0;i<m;i++){
			scanf("%d",&t);
			auto p = std::lower_bound(a,a+n,t);
			if(p==a+n || *p!=t) printf("%d not found\n",t);
			else printf("%d found at %d\n",t,p-a+1);
		}
	}
	return 0;
}
