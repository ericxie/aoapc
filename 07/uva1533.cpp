#include <cstdio>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

const std::vector< std::vector<int> > T[16] ={
{{0}},									//0
{{2,4,7,11},{3,6,10,15}},				//1
{{4,7,11},{5,9,14}},					//2
{{5,8,12},{6,10,15}},					//3
{{5,6},{2,1},{8,13},{7,11}},			//4
{{9,14},{8,12}},						//5
{{3,1},{5,4},{9,13},{10,15}},			//6
{{4,2,1},{8,9,10}},						//7
{{9,10},{5,3}},							//8
{{5,2},{8,7}},							//9
{{6,3,1},{9,8,7}},						//10
{{7,4,2,1},{12,13,14,15}},				//11
{{13,14,15},{8,5,3}},					//12
{{12,11},{14,15},{8,4},{9,6}},			//13
{{9,5,2},{13,12,11}},					//14
{{10,6,3,1},{14,13,12,11}}				//15
};

int dist[1<<15];

struct node{
	int step;
	int flag;
	std::string move;
	node() = default;	
	bool operator < (const node &rhs) const{
		if(step == rhs.step) return move > rhs.move;
		return step > rhs.step;
	}
	void out(FILE *fp){
		fprintf(fp,"%d,",step);
		size_t n = step << 1;
		for(size_t i = 0; i< n; i++) fprintf(fp,"%d%c",move[i]-'a',",\n"[i==n-1]);
	}
};

typedef std::priority_queue<node> PQ;

#define set(x,p) (x |=  (1<<(p)))
#define clr(x,p) (x &= ~(1<<(p)))
#define ts1(x,p) (x & (1<<(p)))
#define ts0(x,p) (~(x) & (1<<(p)))



int bfs(int start){
	PQ Q;
	int end = ~start & 0x7fff;
	memset(dist,-1,sizeof(dist));
	node st;	
	st.step = 0;
	st.flag = start;
	st.move = "";
	Q.push(st);
	while(!Q.empty()){
		auto x  = Q.top();
		Q.pop();
		int u = x.flag;
		if(u == end) {
			x.out(stdout);
			return 1;
		}
		//x.out(stderr);
		for(int i = 0;i<15;i++) if(ts1(u,i)){		
			for(auto arr : T[i+1]){				
				std::vector<int>::iterator it;
				for(it = arr.begin(); it != arr.end(); ++it) {
					//fprintf(stderr,"%x %d : %x\n",u,*it-1, ts0(u,*it-1));
					if(ts0(u,*it-1)) break;
				}
								
				auto last = it;
				if(last == arr.end() || last == arr.begin()) continue;				
				int v = u;
				clr(v,i);
				for(it = arr.begin(); it != last; ++it) clr(v,*it-1);
				set(v,*last-1);
				//fprintf(stderr,"%d,",i+1);
				//for(it = arr.begin(); it != last; ++it) fprintf(stderr,"%d,",*it);
				//fprintf(stderr,"%d | ",*last);
				//fprintf(stderr,"%x %x : %d %d\n",u,v,dist[u],dist[v]);

				if(dist[v] != -1 && dist[v] < dist[u] + 1) continue;
				


				node next;
				next.step = x.step + 1;				
				next.flag = v;
				next.move = x.move;
				next.move.push_back('a'+i+1);
				next.move.push_back('a'+*last);
				dist[v] = dist[u] + 1;								
				Q.push(next);				
			}
		}
	}
	return 0;
}

int main(){
	int ca,s,t;
	//freopen("1533.log","w",stderr);
	/*scanf("%d",&ca);
	while(ca--){
		scanf("%d",&s);
		t = (1<<15) - 1;
		clr(t,s-1);
		
		if(!bfs(t)) puts("IMPOSSIBLE");		
	}	*/
	for(int i = 0; i<15; i++){
		int t = (1<<15) - 1;
		clr(t,i);
		if(!bfs(t)) puts("IMPOSSIBLE");
	}
	return 0;
}