#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

struct point{
	int x,y,c;
	point(int _x,int _y,int _c):x(_x),y(_y),c(_c){};	
};

int solve(std::vector<point> &pts,int k){
	int i,n,x,y;
	n = pts.size();	
	std::vector<double> arc;
	for(i=0; i<n; i++){
		if(i==k) continue;
		x = pts[i].x - pts[k].x;
		y = pts[i].y - pts[k].y;
		if(pts[i].c == 1) x = -x, y = -y;
		arc.push_back(atan2(y,x));
		//fprintf(stderr,"%d : %d %d , %d %d %f\n",i,pts[i].x,pts[i].y,x,y,arc.back());
	}	
	std::sort(arc.begin(),arc.end());
	for(i = 0;i<n-1 && arc[i] < 0; i++) arc.push_back(arc[i] + M_PI * 2);
	//for(auto u : arc) fprintf(stderr,"%.3f,",u);
	//fprintf(stderr,"\n");
	int ans = 0;	
	auto end = arc.begin() + n - 1;
	for(auto it = arc.begin(); it != end ;it++){		
		auto it1 = std::upper_bound(it,arc.end(),*it + M_PI);
		auto len = std::distance(it,it1) + 1;
		//fprintf(stderr,"%d : %d\n",len,ans);
		if(len > ans) ans = len;
	}
	return ans;	
}

int main(){
	int n,i,x,y,c,ans,t;
	while(scanf("%d",&n),n){
		if(n <= 3) {
			ans = n;
			for(i=0;i<n;i++) scanf("%d %d %d",&x,&y,&c);
		} else {
			std::vector<point> pts;
			for(i=0;i<n;i++) {
				scanf("%d %d %d",&x,&y,&c);
				pts.emplace_back(x,y,c);
				//fprintf(stderr,"%d : %d %d %d\n",i,x,y,c);
			}		

			ans = 0;
			for(i=0;i<n;i++) {
				t = solve(pts,i);
				if(t > ans) ans = t;
			}	
		}	
		printf("%d\n",ans);
	}
	return 0;
}

