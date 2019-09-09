#include <cstdio>
#include <cstring>

int isPalindromes(char *s){
	char *p,*q;
	for(q=s;*q;q++);
	for(p=s,q--; p<q && *p==*q; p++,q--);
	return p >= q;
}

int isMirror(char *s){
	char *p,*q;
	char a[]="AEHIJLMOSTUVWXYZ12358";
	char b[]="A3HILJMO2TUVWXY51SEZ8";
	int i,n= strlen(a);
	for(q=s;*q;q++);
	for(p=s,q--; p<=q; p++,q--){
		for(i=0; i<n && a[i]!=*p; i++);
		if(i<n && *q == b[i]) continue;
		return 0;
	}
	return 1;
}

int main(){
	int flag;
	char s[33];
	char res[4][33]={"-- is not a palindrome.",
	                 "-- is a regular palindrome.",
	                 "-- is a mirrored string.",
	                 "-- is a mirrored palindrome."};
	while(gets(s)){
		flag = isPalindromes(s);
		flag |= isMirror(s) << 1;
		printf("%s %s\n\n",s,res[flag]);
	}
	return 0;
}