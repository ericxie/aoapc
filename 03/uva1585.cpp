#include <cstdio>

int main(){
	int T,i,ans;
	char s[111],*p;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		for(p=s,ans=0,i=0;*p;p++){
			if(*p=='O') ans+=++i;
			else i=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}