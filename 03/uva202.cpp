#include <cstdio>
#include <cstring>
#define N 3033

int r[N],q[N];

void solve(int x,int y){
	int i,len,L,R;
	memset(r,-1,sizeof(r));
	for(R=0; r[x]==-1; x%=y){
		r[x] = R;
		x *= 10;
		q[R++] = x / y;
	}
	L = r[x];
	len = R - L;
	for(i=0;i<L;i++) putchar('0'+q[i]);
	putchar('(');
	if(len <= 50){
		for(i=L;i<R;i++) putchar('0'+q[i]);
	} else {
		for(i=L;i<L+50;i++) putchar('0'+q[i]);
		printf("...");
	}
	puts(")");
	printf("   %d = number of digits in repeating cycle\n\n",len);
}


int main(){
	int a,b;
	while(scanf("%d %d",&a,&b)!=EOF){
		printf("%d/%d = %d.",a,b,a/b);
		solve(a%b,b);
	}
	return 0;
}