#include <cstdio>
#include <vector>
int t[32] = {0,0,1,1,0,1,0,1,0,0,
	         0,1,0,1,0,0,0,1,0,1,
	         0,0,0,1,0,0,0,0,0,1,
	         0,1};

std::vector<std::vector<int> > ans[17];


void dfs(int *a,int mask,int k,int n){
	
	if(k==n){	
		//for(int i = 0;i<k;i++) printf("%d ",a[i]);
		//printf(",%02x %d %d\n",mask,k,n);	
		if(t[a[n-1]+1]) ans[n].push_back(std::vector<int>(a,a+n));
		return;
	}
	int i;
	for(i = (~k&1) + 2; i<=n;i+=2) {
		//printf("%d : %02x %d\n",i,(~mask & (1 << i)),i+a[k-1]);
		if((~mask & (1 << i)) && t[i+a[k-1]]){
			a[k] = i; 
			dfs(a,mask | (1<<i),k+1,n);
		}
	}
}

int main(){
	int i,a[16],k=0,n;
	a[0] = 1;
	ans[1].push_back(std::vector<int>(a,a+1)); 
	for(i=2;i<=16;i+=2) dfs(a,1,1,i);
	while(~scanf("%d",&n)){
		if(k) putchar('\n');
		printf("Case %d:\n",++k);
		for(auto &x : ans[n]){
			int m = x.size();
			for(i=0;i<m;i++) printf("%d%c",x[i]," \n"[i==m-1]);
		}

	}
	return 0;
}