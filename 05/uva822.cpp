#include <cstdio>
#include <vector>

struct task{
	int id;
	int cnt;
	int time;
	int duration;
	int interval;
	std::vector<int> sid;
	task() = default;
	inline void read(){
		scanf("%d %d %d %d %d",&id,&cnt,&time,&duration,&interval);
	}
};

std::vector<task> tasks;

struct stuff{
	int id;
	int time;
	std::vector<int> kid;
	stuff() = default;
	inline void read(){
		int i,n;
		scanf("%d %d",&id,&n);
		kid.reserve(n);
		time = 0;
		for(i=0;i<n;i++){
			scanf("%d",&(kid[i]));
			for(auto &x : tasks) if(x.id == kid[i]) x.sid.push(id);
		}
	}
};

std::vector<stuff> stuffs;

void read(){
	int n;
	scanf("%d",&n);
	tasks.reserve(n);
	for(auto &x: tasks) x.read();

	scanf("%d",&n);
	stuffs.reserve(n);
	for(auto &x: stuffs) x.read();
}



void solve(){
	for()
}
