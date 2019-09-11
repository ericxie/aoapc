#include <cstdio>
#include <cstring>

void sum(int n,int *c){
	int i,x;
	for(i=1;i<=n;i++){
		for(x=i;x;x/=10) c[x%10]++;
	}
}

int main(){
	int T,n,i,c[10];
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(c,0,sizeof(c));
		sum(n,c);
		for(i=0;i<10;i++) printf("%d%c",c[i]," \n"[i==9]);
	}
	return 0;
}