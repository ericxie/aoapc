#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
const double eps = 1e-6;

struct rect{
	double x1,y1,x2,y2,area,ratio;
	std::string name;
	int level;
	rect(){}
	rect(std::string &name,double px,double py,double qx,double qy):name(name){
		x1 = std::min(px,qx);
		y1 = std::min(py,qy);
		x2 = std::max(px,qx);
		y2 = std::max(py,qy);
		area = (x2-x1) * (y2 - y1);
		ratio = fabs((y2-y1) / (x2 - x1) - 0.75);
	}
	bool operator<(const rect &rhs) const{
		return area > rhs.area;
	}
	void out() const{
		std::cout << name <<  ':' <<level << ',' << area << ',' << ratio << "=" << x1 << ',' << y1 << ',' << x2 << ',' << y2 << '\n';
	}
};

std::vector<rect> maps;

struct point{
	double x,y;
	point(double x,double y):x(x),y(y){}
	inline bool in(const rect &m) const{
		return x >= m.x1 && x <= m.x2 && y >= m.y1 && y<= m.y2;
	}
	inline double distr(const rect &m) const{
		return (x - m.x2)*(x - m.x2) + (y - m.y1) * (y - m.y1);
	}
	inline double distc(const rect &m) const{
		double cx,cy,d;
		cx = (m.x2 + m.x1) / 2.0;
		cy = (m.y2 + m.y1) / 2.0;
		d = (x - cx)*(x - cx) + (y - cy)* (y - cy);
		return d;
	}
	inline void out() const{
		std::cout << x << ',' << y << '\n';
	}
};

std::map<std::string,point> locations;

void read_maps(){
	std::string buf;
	double x1,x2,y1,y2;
	std::cin >> buf;
	while(std::cin >> buf,buf != "LOCATIONS"){
		std::cin >> x1 >> y1 >> x2 >> y2;
		maps.emplace_back(buf,x1,y1,x2,y2);		
	}
	std::sort(maps.begin(),maps.end());
}

void read_locations(){
	std::string buf;
	double x,y;
	while(std::cin >> buf, buf != "REQUESTS"){
		std::cin >> x >> y;
		locations.emplace(buf,point(x,y));
	}
}

bool cmp(const rect &a,const rect &b,const point &p){
	if(a.level == b.level){		
		double dap = p.distc(a),dbp = p.distc(b);
		if(fabs(dap - dbp) < eps){
			if(fabs(a.ratio - b.ratio) < eps){
				dap = p.distr(a);
				dbp = p.distr(b);
				if(fabs(dap - dbp) < eps){
					return a.x1 > b.x1;
				}
				return dap < dbp;
			}
			return a.ratio > b.ratio;
		}
		return dap > dbp;
	}
	return a.level < b.level;
}

void query(){
	std::string buf;
	int level;
	while(std::cin >> buf, buf != "END"){
		std::cin >> level;
		std::cout << buf << " at detail level " << level ;
		auto it = locations.find(buf);
		if(it == locations.end()){
			std::cout << " unknown location\n";
			continue; 
		}
		bool flag = true;
		int cur_level = 0;
		double last_area = 1e100;
		rect ans;
		for(auto x : maps) {			
			if(it->second.in(x)){
				if(last_area - x.area > eps) ++cur_level;
				x.level = cur_level;
				last_area = x.area;
				if(cur_level > level) break; 				
				if(flag || cmp(ans,x,it->second)){
					ans = x;
				}  				
				flag = false;
			}
		}
		if(flag) std::cout << " no map contains that location\n";
		else if(ans.level < level)	std::cout << " no map at that detail level; using " << ans.name << '\n';
		else std::cout << " using " << ans.name << '\n';
	}
}


int main(){
	read_maps();
	read_locations();
	query();
	return 0;
}