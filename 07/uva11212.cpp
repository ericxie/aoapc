#include <cstdio>

inline int hx(int *a,int sz){
	int ret = 0,i;
	for(i=0; i< sz-1; i++) ret += a[i+1] != a[i] + 1;
	return ret; 
}

inline void trans(int *a,int *b,int sz,int start,int end,int pos){
	int i,j;
	for(i=j=0;i<start;i++,j++) b[j] = a[i];
	for(i=end;i<pos;i++,j++) b[j] = a[i];
	for(i=start;i<end;i++,j++) b[j] = a[i];
	for(i=pos;i<sz;i++,j++) b[j] = a[i];
}

int dfs(int maxd,int d,int *a,int n,int h){
	// fprintf(stderr,"%d %d:",maxd,d);
	// for(int i = 0;i < n; i++) fprintf(stderr,"%d ",a[i]);
	// fprintf(stderr," = %d\n",h);
	if(d == maxd){
		if(h==0){
			printf("%d\n",d);
			return 1;
		} else return 0;
	} 
	if(d*3 + h > maxd * 3) return 0;
	int m = (n + 1) >> 1;
	int b[11],hb;
	for(int i = 0; i < n-1; i++){
		for(int j = 1; j<=m && i+j < n;j++){
			if(a[i+j] == a[i+j-1] + 1) continue;
			for(int k = i+j+1; k<=n; k++){
				// fprintf(stderr, "   %d %d %d\n",i,j,k);
				trans(a,b,n,i,i+j,k);
				hb = hx(b,n);
				if(hb > h) continue;
				if(dfs(maxd,d+1,b,n,hb)) return 1;
			}
		}
	}
	return 0;
}

int ida(int *a,int n){
	int depth,ok,h;
	h = hx(a,n);
	for(depth = 0; depth<n ; depth++){
		if(dfs(depth,0,a,n,h)) return 1;
	}
	return 0;
}

int main(){
	int a[11],i,n,k=0;
	while(scanf("%d",&n),n){
		printf("Case %d: ",++k);
		for(i=0;i<n;i++) scanf("%d",a+i);
		ida(a,n);
	}
	return 0;
}