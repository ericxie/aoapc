#include <cstdio>

const int ans[15][33]={
{9,4,1,6,4,11,2,14,11,15,6,1,10,10,7,11,4,4,1},
{9,7,2,1,4,10,1,14,2,1,7,11,14,15,13,13,4,7,2},
{9,10,3,1,6,7,1,12,3,1,10,14,12,11,13,13,6,15,3},
{9,1,4,6,1,13,6,10,3,11,13,3,12,15,11,11,2,1,4},
{10,12,5,3,8,15,12,6,13,7,9,1,7,10,8,7,9,11,14,14,5},
{9,1,6,4,1,13,4,7,2,15,13,2,14,11,15,15,3,1,6},
{9,1,7,6,1,11,4,9,7,14,11,11,2,15,6,6,4,1,7},
{10,3,8,12,5,15,3,13,6,1,10,2,9,11,2,14,5,2,9,10,8},
{10,2,9,11,2,12,5,3,8,13,4,1,7,14,5,15,3,3,8,7,9},
{9,1,10,4,1,11,4,4,6,12,5,10,8,15,12,12,3,1,10},
{9,4,11,1,4,10,1,14,2,1,7,11,14,15,13,13,4,4,11},
{9,14,12,2,14,7,2,1,4,15,13,3,15,11,14,4,13,15,12},
{9,4,13,1,4,11,2,13,11,15,13,2,14,3,15,15,12,11,13},
{9,11,14,2,11,3,12,10,3,1,6,11,13,15,12,6,13,12,14},
{9,6,15,1,6,7,1,12,3,1,10,15,12,11,13,13,6,6,15}
};

int main(){
	int T,t,i,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&t);
		t--;
		n = ans[t][0];
		printf("%d\n",n);
		n <<= 1;
		for(i=1;i<=n;i++) printf("%d%c",ans[t][i]," \n"[i==n]);
	}
	return 0;
}