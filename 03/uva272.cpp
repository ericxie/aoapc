#include <stdio.h>

int main(){
	char c;
	int flag = 0;
	while((c = getchar())!=EOF){
		if(c=='"'){
			flag ^= 1;
			if(flag) printf("``");
			else printf("''");
		} else putchar(c);
	}
	return 0;
}