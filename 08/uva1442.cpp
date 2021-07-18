#include <cstdio>

const int N = 1e6+2;
int s[N],p[N],f[N];

int main(){
	int T,n,i,ans;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(i=0;i<n;i++) scanf("%d",p+i);
		for(i=0;i<n;i++) scanf("%d",s+i);
		f[0] = s[0];
		for(i=1;i<n;i++){
			f[i] = f[i-1];			
			if(f[i] < p[i]) f[i] = p[i];
			else if(f[i] > s[i]) f[i] = s[i]; 			
		}
		ans = f[n-1] - p[n-1];
		for(i=n-2;i>=0;i--){
			if(f[i] > f[i+1]) f[i] = f[i+1];		
			if(f[i] < p[i]) f[i] = p[i];
			ans += f[i] - p[i];
		}
		
		printf("%d\n",ans);
		// for(i=0;i<n;i++) printf("%d ",f[i]);
		// putchar('\n');
		// for(i=0;i<n;i++) printf("%d ",p[i]);
		// putchar('\n');
	}
	return 0;
}