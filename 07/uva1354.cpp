#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>



std::set<std::pair<double,double> > tree[1<<6];
int weight[1<<6];
bool vis[1<<6];
int stone[6];
double limit;

void init(int n){
	int i=0,j;
	for(i=1;i<(1<<n);i++) {
		tree[i].clear();
		vis[i] = false;
		weight[i] = 0;
		for(j=0;j<n;j++) if(i&(1<<j)) weight[i] += stone[j];
	}
	for(i=0;i<n;i++) {
		tree[1<<i].emplace(0.0,0.0);
		vis[1<<i] = true;
	}
}

void dfs(int u,int n){
	int i,j;
	vis[u] = true;
	double tl,tr,left,right;
	if(u){
		for(i = (u - 1) & u; i; i = (i - 1) & u){
			j = u ^ i; 
			if(j==0) continue;
			
			if(!vis[i]) dfs(i,n);
			if(!vis[j]) dfs(j,n);
			//fprintf(stderr,"%02x %02x %02x : \n",u,i,j);
			//fprintf(stderr,"%x : %lld, %x : %lld\n",i,tree[i].size(),j,tree[j].size());
			for(auto x : tree[i]) for(auto y : tree[j]){
				tl = 1.0 * weight[j] / (weight[i] + weight[j]);
				tr = 1.0 * weight[i] / (weight[i] + weight[j]);
				//fprintf(stderr,"  %g %g, %g %g, %g %g\n",tl,tr,x.first,x.second,y.first,y.second);
				// L R
				left  = std::max(x.first + tl, y.first - tr);
				right = std::max(tr + y.second, x.second - tl);
				if(left + right < limit)  tree[u].emplace(left,right);
				// // R R
				// left  = std::max(x.second + tl, y.first - tr);
				// right = std::max(tr + y.second, x.first - tl);
				// if(left + right < limit)  tree[u].emplace(left,right);
				// // L L
				// left  = std::max(x.first + tl, y.second - tr);
				// right = std::max(tr + y.first, x.second - tl);
				// if(left + right < limit)  tree[u].emplace(left,right);
				// // R L
				// left  = std::max(x.second + tl, y.second - tr);
				// right = std::max(tr + y.first, x.second - tl);
				// if(left + right < limit)  tree[u].emplace(left,right);
			}			
		}
		//fprintf(stderr,"\n%02x : \n",u);
		//for(auto x : tree[u]) fprintf(stderr,"==%g %g : %g\n", x.first, x.second, x.first+x.second);		
	} 
}

int main(){
	int T,n,s;
	scanf("%d",&T);
	while(T--){
		scanf("%lf %d",&limit,&n);
		for(int i=0;i<n;i++) scanf("%d",stone+i);
		init(n);
		s = (1<<n) - 1;
		dfs(s,n);
		if(tree[s].empty()) puts("-1");
		else {
			double ans = 0.0;
			for(auto x : tree[s]){
				if(ans < x.first + x.second) ans = x.first + x.second;
			}
			printf("%.16f\n",ans);	
		}		
	}
	return 0;
}