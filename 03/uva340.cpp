#include <cstdio>
#include <cstring>
#include <algorithm>

int main(){
	int n,k=0,i;
	int a[1011],b[1011],c[11],d[11],e[11],s,w;
	while(scanf("%d",&n),n){
		printf("Game %d:\n",++k);
		memset(c,0,sizeof(c));
		
		for(i=0;i<n;i++) scanf("%d",a+i),c[a[i]]++;
		for(;;){
			memset(d,0,sizeof(d));
			memcpy(e,c,sizeof(c));
			s = w = 0;
			for(i=0;i<n;i++){
				scanf("%d",b+i),d[b[i]]++;
				if(a[i] == b[i]) s++,e[a[i]]--,d[b[i]]--;	
			}	
			if(b[0] == 0) goto next;
			for(i=1;i<10;i++) w += std::min(e[i],d[i]);
			printf("    (%d,%d)\n",s,w);
		}		
next: ; 
	}
	return 0;
}