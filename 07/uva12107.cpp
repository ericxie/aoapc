#include <cstdio>

const char sigma[]="*0123456789";

inline bool equal(char *s){
	int a=0,b=0;
	char *p,*q;	
	for(p=s;*p!=' ';p++) a*=10, a+=*p - '0'; 
	for(p++;*p!=' ';p++) b*=10, b+=*p - '0'; 
	a*=b;
	for(q=p+1;*q;q++);
	for(q--;q>p&&a;q--,a/=10) if(*q!='*' && *q!= a%10+'0') break;		
	return !a && p == q;
}

int check(char *s,int k,int b){
	int cnt = 0,i;	
	if(s[k] == ' ') k++,b++;
	if(b==2){		
		cnt = equal(s);		
		return cnt;
	}
	char ch = s[k];
	if(s[k] == '*'){
		if(k==0 || s[k-1] == ' ') i = 2;
		else i = 1;
		for(;i<11;i++){
			s[k] = sigma[i];
			cnt += check(s,k+1,b);
			if(cnt > 1) break;
		}
	} else {
		cnt += check(s,k+1,b);
	}
	s[k] = ch;
	return cnt;
}

int dfs(char *s,int k,int d,int maxd){
	if(d == maxd) return check(s,0,0) == 1;
	if(!s[k]) return 0;
	if(s[k] == ' ') k++;	
	char ch = s[k];
	for(int i=0;i<11;i++){
		if(i==1 && (k==0 || s[k-1] == ' ')) continue;
		if(s[k] != sigma[i]){
			s[k] = sigma[i];
			if(dfs(s,k+1,d+1,maxd)) return 1;
			s[k] = ch;
		} else {
			if(dfs(s,k+1,d,maxd)) return 1;
		}		
	}	
	return 0;
}

int main(){
	char s[22];
	int i,k = 0;
	
	while(gets(s),s[0] != '0'){
		printf("Case %d: ",++k);
		for(i=0;;i++) if(dfs(s,0,0,i)){		
			puts(s);
			break;
		}	
	}
	return 0;
}

