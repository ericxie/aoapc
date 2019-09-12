#include <cstdio>

int solve(char *s,char *t){
	while( *s && *t){
		if( *s == *t) s++;
		t++;
	}
	return !(*s);
}

int main(){
	char s[11111],t[11111];
	while(scanf("%s %s",s,t)!=EOF){
		puts(solve(s,t)?"Yes":"No");
	}
	return 0;
}