#include <cstdio>
#include <unordered_map>

std::unordered_map<int,int> hash;
int a[4000],b[4000],c[4000],d[4000];

int main(){
	int T,n,i,j,ans,t;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		hash.clear();
		for(i=0;i<n;i++) scanf("%d %d %d %d",a+i,b+i,c+i,d+i);
		for(i=0;i<n;i++) for(j=0;j<n;j++){
			t = a[i] + b[j];
			auto it = hash.find(t);
			if(it == hash.end()) hash.emplace(t,1);
			else it->second++;		
		}
		ans = 0;		
		for(i=0;i<n;i++) for(j=0;j<n;j++){
			t = - (c[i] + d[j]);
			auto it = hash.find(t);
			if(it != hash.end()) ans += it->second;
		}
		printf("%d\n",ans);
		if(T) putchar('\n');
	}
	return 0;
}