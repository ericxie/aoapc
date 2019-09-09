#include <cstdio>
#include <cstring>
int main(){
	char a[]="1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./";
	char b[]="`1234567890-QWERTYUIOP[]ASDFGHJKL;ZXCVBNM,.";
	char c;
	int i,n = strlen(a);
	while((c = getchar())!=EOF){
		for(i=0; i<n && c != a[i]; i++);
		if(i<n)	putchar(b[i]);
		else putchar(c);			
	}
	return 0;
}