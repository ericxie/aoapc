#include <cstdio>
#include <cstring>
#include <algorithm>

void cnt(char *s,int *c){
	memset(c,0,sizeof(int)*26);
	while(*s) c[*s++ - 'A']++;
}

bool cmp(int *a,int *b){
	int i;
	std::sort(a,a+26);
	std::sort(b,b+26);
	for(i=0;i<26 && a[i] == b[i];i++) ;
	return i==26;
}

int main(){
	char a[111],b[111];
	int ca[26],cb[26];
	while(scanf("%s %s",a,b)!=EOF){
		cnt(a,ca);
		cnt(b,cb);
		puts(cmp(ca,cb)?"YES":"NO");
	}
	return 0;
}