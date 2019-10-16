#include <cstdio>
const int N = 111;

int q[N];
int head,tail;

int main(){
	int n,i;
	while(scanf("%d",&n),n){
		printf("Discarded cards:");
		head = tail = 0;
		for(i=1;i<=n;i++) q[tail++] = i;
		while(tail!=head+1){
			printf(" %d",q[head++]);
			if(--n==1) break;
			putchar(',');
			q[tail++] = q[head++];
		}
		printf("\nRemaining card: %d\n",q[head]);		
	}
	return 0;
}