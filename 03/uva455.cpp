#include <cstdio>
#include <cstring>

void getFail(int *fail,int n,char *s){
	int i,j;
	fail[0] = 0;
	for(i=1; i<n; i++){
		for(j=fail[i-1]; j && s[i]!=s[j]; j = fail[j-1]) ;
		fail[i] = j + (s[i] == s[j]);
	}
}

int main(){
	char s[111];
	int fail[111],n,T,t;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		n =  strlen(s);
		getFail(fail,n,s);
		t = n - fail[n-1];
		printf("%d\n",n%t?n:t);
		if(T) putchar('\n');
	}
	return 0;
}