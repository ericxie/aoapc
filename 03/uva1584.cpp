#include <cstdio>
#include <cstring>

int main(){
	int T,n,i,k;
	char s[222];
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		n = strlen(s);
		for(i=0;i<n;i++) s[i+n] = s[i];
		s[n+n]=0; 
		for(i=1,k=0;i<n;i++) if(strncmp(s+i,s+k,n) < 0) k=i;
		s[k+n] = 0;
		printf("%s\n",s+k);
	}
	return 0;
}