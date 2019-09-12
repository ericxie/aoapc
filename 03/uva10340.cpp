#include <cstdio>

int solve(char *s,char *t){
	while( *s && *t){
		if( *s == *t) s++;
		t++;
	}
	return !(*s);
}

int main(){
	char s[1111],t[1111];
	while(scanf("%s %s",s,t)!=EOF){
		puts(solve(s,t)?"Yes":"No");
	}
	return 0;
}