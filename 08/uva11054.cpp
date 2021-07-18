#include <cstdio>
#include <cstdlib>
int a[100011];

int main(){
	int n,i,j,t;
	long long ans;
	while(scanf("%d",&n),n){
		for(i=0;i<n;i++) scanf("%d",a+i);
		for(i=0;i<n && a[i] >= 0; i++);
		for(j=0;j<n && a[j] <= 0; j++);
		ans = 0;
		while(i<n && j<n){
			t = a[i]+a[j];
			if(t<0) {
				a[i] += a[j];
				ans +=(long long) abs(j - i) * a[j];
				a[j] = 0;
				for(;j<n && a[j] <= 0; j++);
			} else if(t > 0){
				a[j] += a[i];
				ans +=(long long) abs(j - i) * -a[i];
				a[i] = 0;
				for(;i<n && a[i] >= 0; i++);
			} else {
				ans +=(long long) abs(j - i) * a[j];
				a[i] = a[j] = 0;
				for(;i<n && a[i] >= 0; i++);
				for(;j<n && a[j] <= 0; j++);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}