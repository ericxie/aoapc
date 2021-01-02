#include <cstdio>
#include <cstring>
typedef unsigned int uint;
const uint N = 15;
const uint inf = N<<1;


uint G[N];

inline uint next(uint x){
	uint s,r;
	s = x & (-x);
	r = s + x;
	x = r | (((x^r)>>2) / s);
	return x;
}

bool dfs(uint mask,uint &vis,int n,int u,int fa){
	//fprintf(stderr,"%x %x %d %d %d:\n",mask,vis,n,u,fa);
	vis |= 1u << u;
	int cnt = 0,v;
	uint m = G[u] & ~mask;
	//fprintf(stderr,"%u : %x\n",u,m);
	for(v=0; v<n; v++) if(m & (1u << v)){
		if(v == fa) continue;
		if(vis & (1 << v)) return false;
		cnt++;
		if((fa==-1 && cnt > 2) || (fa!=-1 && cnt > 1)) return false; 
		
		if(!dfs(mask,vis,n,v,u)) return false;
	}
	return true;
}

uint dfu(uint mask,uint n,uint k){
	uint i,c,vis=mask;	
	c = 0;
	for(i=0; i<n ; i++) if(~vis & (1<<i)){
		c++;
		if(!dfs(mask,vis,n,i,-1)) return inf;
	}
	return c - 1 > k ? c - 1 : k;
}

int solve(uint n){
	uint i,s,t;
	s = dfu(0,n,0);
	//fprintf(stderr," s = %u\n",s);
	for(i=1;i<n&&i<s;i++){
		uint begin = (1u << i) - 1;
		uint end = begin << (n - i);
		uint mask;
		
		for(mask=begin;mask<=end&&i<s;mask = next(mask)){
			t = dfu(mask,n,i);
			//fprintf(stderr,"  %u %x :  t = %u\n",i,mask,t);
			if(t < s) s = t;
		}
		
	}
	return s;
}

int main(){
	int n,u,v,k=0;
	while(scanf("%d",&n),n){
		memset(G,0,sizeof(G));
		while(scanf("%d %d",&u,&v),u!=-1&&v!=-1){
			G[u-1] |= 1<<(v-1);
			G[v-1] |= 1<<(u-1);
		}
		//for(u=0;u<n;u++) fprintf(stderr,"%u:%x\n",u,G[u]);
		printf("Set %d: Minimum links to open is %d\n",++k,solve(n));
	}
	return 0;
}