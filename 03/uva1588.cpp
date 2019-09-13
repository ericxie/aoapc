#include <cstdio>
#include <cstring>
#define N 1111

int match(char *t,int n,char *p,int m){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++)
			if(t[i+j]=='2' && p[j]=='2') break;
		if(j==m) return i+j>n?i+j:n;
	}
	return n+m;  
}


int main(){
	char a[N],b[N];
	while(scanf("%s %s",a,b)!=EOF){
		int n,m,ans,len;
		n = strlen(a);
		m = strlen(b);
		ans = n + m;
		memset(a+n,'1',m);
		memset(b+m,'1',n);

		len = match(a,n,b,m);
		if(len < ans) ans = len;
		
		len = match(b,m,a,n);
		if(len < ans) ans = len;

		printf("%d\n",ans);
	}
	return 0;
}