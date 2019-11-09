#include <cstdio>
#include <cstring>
const int N= 222;
int sum[N];
int cnt;
void build(int idx){
	int r;
	scanf("%d",&r);
	if(r!=-1){
		cnt++;
		sum[idx] += r;
		build(idx - 1);
		build(idx + 1);
	}
}

int main(){
	int T=0,i;
	for(;;){
		memset(sum,0,sizeof(sum));
		cnt = 0;
		build(N>>1);
		if(!cnt) break;
		printf("Case %d:",++T);
		for(i=0;i<N && !sum[i];i++);
		printf("\n%d",sum[i]);
		for(i++;i<N && sum[i];i++) printf(" %d",sum[i]);
		printf("\n\n");
	}
	return 0;
}