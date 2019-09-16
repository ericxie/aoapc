#include <cstdio>
#include <cstring>

int offset[8];
char buf[11111],text[11111],cipher[11111];


void init(){
	for(int i=1; i<8; i++) offset[i] = offset[i-1] + (1 << i) - 1;
}

int bin2int(char *s,int width){
	int ret = 0;
	while(width--){
		ret <<= 1;
		ret |= *s++ -'0';
	}
	return ret;
}

void solve(char *text,char *cipher){
	int width ,idx,endtag;	
	
	while(*cipher){		
		width = bin2int(cipher,3);		
		endtag = (1 << width) - 1;
		cipher += 3;
		while(*cipher){
			idx = bin2int(cipher,width);
			cipher += width;
			if(idx == endtag) break;
			idx += offset[width-1];			
			putchar(text[idx]);
		}
	}
	putchar('\n');	
}

int main(){
	
	cipher[0] = 0;
	init();
	while(gets(buf)){		
		if(buf[0]!='0' && buf[0]!='1') {			
			if(cipher[0]) solve(text,cipher);
			strcpy(text,buf);
			cipher[0] = 0;
		} else 
			strcat(cipher,buf);			
	}
	solve(text,cipher);
	return 0;
}