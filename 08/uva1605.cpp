#include <cstdio>

char s[52];

int main(){
	int n,i,j,first = 0;
	for(i=0;i<26;i++) s[i]='A'+i,s[i+26]='a'+i;
	while(~scanf("%d",&n)){
		if(first) putchar('\n');
		first = 1;
		printf("2 %d %d\n",n,n);
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++) putchar(s[i]);
			putchar('\n');
		}
		putchar('\n');
		for(i=0;i<n;i++){
			for(j=0;j<n;j++) putchar(s[j]);
			putchar('\n');
		}		
	}
	return 0;
}