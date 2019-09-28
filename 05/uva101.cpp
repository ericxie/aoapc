#include <cstdio>
#include <cstring>
#include <stack>
const int N=33;

int prev[N],next[N];

int clean(int x){
	int p = next[x],q;
	while(p){
		q = p;
		p = next[p];
		prev[q] = next[q] = 0;		
	} 
	next[x] = 0;
	return x;
}

int tail(int x){
	int p = x;
	while(next[p]) p= next[p];
	return p;
}

void join(int x,int y){
	next[y] = x;
	next[prev[x]] = 0;
	prev[x] = y;	
}

void out(int n){
	int i,p;
	for(i=1;i<=n;i++){
		printf("%d:",i-1);
		if(!prev[i]) for(p=i;p;p=next[p]) printf(" %d",p-1);
		putchar('\n');
	}
}

int check(int x,int y){
	int p;
	if(x==y) return 0;
	for(p=next[x];p;p=next[p]) if(p==y) return 0;
	for(p=prev[x];p;p=prev[p]) if(p==y) return 0;
	return 1;
}

int main(){
	int n,x,y;
	char buf[111],s1[6],s2[6];
	scanf("%d ",&n);
	while(gets(buf)){
		if(buf[0]=='q') out(n);
		else {
			sscanf(buf,"%s %d %s %d",s1,&x,s2,&y);
			x++,y++;
			if(!check(x,y)) continue;
			switch(s1[0]+s2[1]){
				case 'm'+'n': join(clean(x),clean(y)); break;
				case 'm'+'v': join(clean(x),tail(y)); break;
				case 'p'+'n': join(x,clean(y)); break;
				case 'p'+'v': join(x,tail(y)); break;
			}
			//puts(buf);
			//out(n);	
			//puts("--------------------------------");
		}		
	}
	return 0;
}