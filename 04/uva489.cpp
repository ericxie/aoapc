#include <cstdio>
#include <cstring>

int main(){
	int T,t[26],wrong,i,total;
	char a[1111],b[1111],*p;
	while(scanf("%d",&T),T>0){
		scanf("%s %s",a,b);
		memset(t,0,sizeof(t));
		for(p=a;*p;p++) t[*p-'a'] = 1;
		for(i=0,total=0;i<26;i++) total += t[i];
		printf("Round %d\nYou ",T);
		for(p=b,wrong=0;*p && wrong<7 && total;p++){
			switch(t[*p-'a']){
				case 0: wrong++; t[*p-'a'] = -1; break;
				case 1: total--; t[*p-'a'] = -1; break;
			}			 
		}
		if(wrong>6) puts("lose."); 
		else if(!total) puts("win.");
		else puts("chickened out.");		
	}
	return 0;
}
 