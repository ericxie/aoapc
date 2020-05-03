#include <cstdio>
#include <cmath>
#include <array>
#include <vector>
#include <utility>

const double inf = 1e6;
const double eps = 1e-6;

struct cycle{
	double x,y,r;
	int tag;
	cycle(double x,double y,double r):x(x),y(y),r(r){
		tag = (y <= r) << 1 | (y+r>=1000);
	}	
	cycle() = default;
	bool join(const cycle &a){
		double dist;
		dist = (x - a.x) *  (x - a.x) + (y - a.y) * (y - a.y);
		return dist < r + a.r;
	}
};

const int  N = 1011;

std::array<cycle,N> cycles;
std::array<int,N> vis;
std::array<std::vector<int>,N> G;
typedef std::pair<double,double> PDD;

void build(int n){
	for(int i = 0; i<n; i++) G[i].clear();
	for(int i = 0 ; i < n-1 ; i++){
		for(int j=i+1; j < n; j++){
			if(cycles[i].join(cycles[j])){
				G[i].push_back(j);
				G[j].push_back(i);
				fprintf(stderr,"Edge: %d - %d\n",i+1,j+1);
			}
		}
	}
}

bool dfs(int u){
	int ans = cycles[u].tag;
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]){
		ans |= dfs(v);
		if(ans == 3) break;
	}
	return ans;
}

bool dfu(int n){
	vis.fill(0);
	int ans = 0;
	for(int i = 0; i<n; i++) if(!vis[i]){
		ans |= dfs(i);
		if(ans == 3)  break;
	}
	return ans == 3;
}

std::vector<std::pair<double,double> > segs;

double

void solve(int n){
	if(dfu(n)) puts("IMPOSSIBLE");
	else{
		double left = inf,right = -inf;

	}
}

void read(int n){
	double x,y,r;
	for(int i = 0; i< n ; i++){
		scanf("%lf %lf %lf",&x,&y,&r);
		cycles[i] = cycle(x,y,r);
		cycles[i].out();
	}
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		read(n);
		build(n);
		solve(n);
	}
	return 0;
}