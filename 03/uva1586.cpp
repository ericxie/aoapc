#include <cstdio>

double weight(char c){
	if(c=='C') return 12.01;
	if(c=='H') return 1.008;
	if(c=='O') return 16.0;
	if(c=='N') return 14.01;
}

char *token(char *s,double *ret){
	double w = weight(*s++);
	int cnt = 1;
	if(*s>='1' && *s <='9'){
		cnt = *s++ - '0';
		if(*s>='0' && *s <='9') 
			cnt = cnt * 10 + *s++ - '0'; // <=80
	}  
	*ret = w * cnt;
	return s;
}

int main(){
	int T;
	double ans,t;
	char s[111],*p;

	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		ans = 0.0;
		for(p=s;*p;){
			p = token(p,&t);
			ans += t;
		}
		printf("%.3f\n",ans);
	}
	return 0;
}