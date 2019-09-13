#include <cstdio>
char s[1111111],t[1111111];
int solve(char *s,char *t){
	while( *s && *t){
		if( *s == *t) s++;
		t++;
	}
	return !(*s);
}

int main(){	
	while(scanf("%s %s",s,t)!=EOF){
		puts(solve(s,t)?"Yes":"No");
	}
	return 0;
}