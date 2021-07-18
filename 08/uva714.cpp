#include <cstdio>

int a[555];

int get(long long cap,int n){
	int i,r;
	long long t;
	for(i=t=0,r=1;i<n;i++){
		if(t+a[i] <= cap) t+=a[i];
		else {
			r++;
			t=a[i];
		}
	}
	return r;
}

long long bs(int n,int k,long long L,long long R){
	long long count = R - L + 1;
	while(count > 0){		
		long long step = count >> 1;
		int x = get(L+step,n);		
		if(x > k){
			L += step + 1;
			count -= step + 1;
		} else {
			count = step;
		}
	}
	return L;
}

void out(long long cap,int k,int n){
	int i,j;
	long long t = 0;
	if(n==0) return;
	for(i=n-1;i>=0 && t+a[i] <= cap && k <= i+1;i--) t+=a[i];
	out(cap,k-1,++i);
	if(i!=0) printf(" / ");
	printf("%d",a[i]);
	for(j=i+1;j<n;j++) printf(" %d",a[j]); 
}

int main(){
	int T,n,k,i;
	long long cap,L,R;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&k);
		L=R=0;
		for(i=0;i<n;i++) {
			scanf("%d",a+i);
			if(a[i]>L) L=a[i];
			R += a[i];
		}
		cap = bs(n,k,L,R);
		out(cap,k,n);
		putchar('\n');
	}	
	return 0;
}