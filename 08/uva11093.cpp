#include <cstdio>

const int N = 100001;

int a[N],b[N],c[N<<1];

int main(){
	int T,i,j,k,t,n;
	scanf("%d",&T);
	for(k=1;k<=T;k++){
		printf("Case %d: ",k);
		scanf("%d",&n);
		for(i=0;i<n;i++) scanf("%d",a+i);
		for(i=0;i<n;i++) scanf("%d",b+i);	
		for(i=0;i<n;i++) c[i] =c[n+i] = a[i]-b[i];
		for(i=0;i<n;i++){
			if(c[i]<0) continue;
			t = c[i];
			for(j=i+1;j<(i+n) && t+c[j]>=0;j++) t+=c[j];
			if(j-i >= n) break;
			i=j; 
		}
		if(i<n) printf("Possible from station %d\n",i+1);
		else puts("Not possible");
	}
	return 0;
}