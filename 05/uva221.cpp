#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
const double eps = 1e-6;

struct building{
	double x,y,w,h;
	int idx;
	building(double x,double y,double w,double h,int idx):x(x),y(y),w(w),h(h),idx(idx){}
	bool operator<(const building &rhs) const {
		return x < rhs.x || (fabs(x -  rhs.x) < eps  && y < rhs.y );
	}
	inline bool cover(double cx){ return x <= cx && cx <= x + w; }	
};

std::vector<double> xcor;
std::vector<building> buildings;

bool read(){
	int i,n;
	double x,y,w,d,h;
	scanf("%d",&n);
	if(n==0) return false;
	xcor.clear();
	buildings.clear();
	for(i=0;i<n;i++) {
		scanf("%lf %lf %lf %lf %lf",&x,&y,&w,&d,&h);
		buildings.emplace_back(x,y,w,h,i+1);
		xcor.push_back(x);
		xcor.push_back(x+w);
	}
	return true;
}

bool visible(building & a,double cx){
	for(auto &b : buildings){
		if(b.cover(cx) && b.y < a.y && b.h >= a.h) return false;
	}
	return true;
}

void solve(){

	std::sort(buildings.begin(),buildings.end());
	std::sort(xcor.begin(),xcor.end());
	auto last = std::unique(xcor.begin(), xcor.end());

	std::vector<int> vis;
	for(auto &bd : buildings){
		for(auto it = xcor.begin(); it!= last -1; ++it){
			double cx = (*it + *(it+1)) / 2;
			if(bd.cover(cx) && visible(bd,cx)){
				vis.push_back(bd.idx);
				break;
			}
		}
	}
	for(auto it= vis.begin(); it != vis.end(); ++it) printf("%d%c",*it," \n"[it==vis.end()-1]);
}

int main(){
	int T=0;
	while(read()){
		if(T) putchar('\n');
		printf("For map #%d, the visible buildings are numbered as follows:\n",++T);
		solve();
	}
	return 0;
}

