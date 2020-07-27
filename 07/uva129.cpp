#include <cstdio>

char s[128000];
int n,lmt,id;

void out(int k){
	int i;
	for(i=0;i<k;i++){
		if(i) {
			if(i%64==0) putchar('\n');
			else if(i%4==0)putchar(' ');
		}
		putchar(s[i]);		
	}	
	printf("\n%d\n",k);
}

bool check(int k,char ch){
	int i,j,len;
	s[k] = ch;
	for(len=1;len<=(k+1)>>1;len++){
		for(i=k-(len << 1)+1,j=k-len+1 ; j<=k && s[i]==s[j]; i++,j++);
		if(j>k) return false;
	}
	return true;
}


bool dfs(int k){
	if(id==n) {
		out(k);
		return true;
	} else {
		for(int i=0;i<lmt;i++) if(check(k,'A'+i)){
			id++;
			if(dfs(k+1)) return true;
		}
	}
	return false;
}

int main(){	
	while(scanf("%d %d",&n,&lmt),n!=0){
		id = 0;
		dfs(0);
	}
}