#include <cstdio>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <cmath>
const double eps = 1e-6;

struct building{
	double x,y,w,h;
	int idx;
	building(double x,double y,double w,double h,int idx):x(x),y(y),w(w),h(h),idx(idx){}
	bool operator==(const building &rhs) const{
		return idx == rhs.idx;
	}
	bool operator<(const building &rhs) const {
		return x < rhs.x || (fabs(x -  rhs.x) < eps  && y < rhs.y );
	}
};

std::vector<double> xcor;
std::list<building> buildings;

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

void solve(){

	buildings.sort();
	std::sort(xcor.begin(),xcor.end());
	auto last = std::unique(xcor.begin(), xcor.end());

	std::set<building> vis;

	for(auto it = xcor.begin(); it != last -1 ; ++it){
		double cx = (*it + *(it+1)) / 2;
		std::list<building> mq;
		for(auto p = buildings.begin(); p!= buildings.end();){
			if(p->x > cx) break;
			if(p->x + p->w < cx){
				p = buildings.erase(p);
				continue;
			}
			bool flag = true;
			for(auto q = mq.begin(); q != mq.end();){
				if(q->y < p->y){
					if(q->h >= p->h){
						flag = false;
						break;
					} else ++q;				
				} else if(q->h <= p->h){
					mq.insert(q,*p);
					flag = false;
					q = mq.erase(q);
				} else {
					mq.insert(q,*p);
					flag = false;
					++q;
				}
			}
			if(flag) mq.push_back(*p);
			++p;
		}
		for(auto a:mq) if(vis.find(a) == vis.end())	vis.insert(a);	
	}	
	auto it = vis.begin();
	printf("%d",it->idx);
	for(++it;it != vis.end();++it) printf(" %d",it->idx);
	putchar('\n');
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

