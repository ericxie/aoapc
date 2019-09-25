#include <cstdio>

unsigned int ip[1011];

int check(int mask,int m){
	int i;
	unsigned int k;
	k = ip[0] & mask;
	for(i=1;i<m && (ip[i] & mask) == k;i++);
	return i==m; 
}

void out(unsigned int n){
	printf("%u.%u.%u.%u\n",(n&0xff000000) >> 24,(n&0xff0000) >> 16, (n&0xff00) >> 8, n& 0xff);
}


void solve(int m){
	unsigned int mask;
	for(mask = ~0U; mask>=0 && ! check(mask,m); mask <<= 1);
	out(ip[0] & mask);
	out(mask);	
}



int main(){
	int m,i;
	unsigned int a[4];
	while(scanf("%d",&m)!=EOF){
		for(i=0;i<m;i++){
			scanf("%u.%u.%u.%u",a,a+1,a+2,a+3);
			ip[i] = a[0] << 24 | a[1] << 16 | a[2] << 8 | a[3];
		}
		solve(m);
	}
	return 0;
}