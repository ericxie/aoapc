#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

#define get(x) 'A'+((x)>>1),((x)&1)?'-':'+'

struct Block{
	int in;
	std::set<int> outs;
	int vis;
	Block() = default;
	Block(const std::vector<int> &slots,size_t p){
		in = slots[p];
		//printf("%d => ",in);
		for(size_t i = 0; i < slots.size(); i++) if(i!=p) {
			int q = slots[i];
			if(q & 1) q--;
			else q++;
			outs.insert(q);
			//printf("%d,",q);
		}
		//printf("\n");
		vis = 0; 
	}
	bool operator<(const Block &rhs) const{
		if(in < rhs.in) return true;
		return outs < rhs.outs;
	}
	void out(){ 
		printf("%c%c=>",get(in)); 
		for(auto x : outs) 
			printf("%c%c,",get(x));
		printf("\n");
	};
};

std::set<int> nodes[26<<1];
std::set<Block> pool;
std::vector<Block> blocks;

void dout(){
	for(int i=0;i<52;i++) if(!nodes[i].empty()){
		printf("%c%c : ",get(i));
		for(auto x : nodes[i]){
			printf("%d,",x);
		}
		printf("\n");
	}
	puts("-----------");
	int id = 0;
	for(auto x: blocks) {
		printf("%d : ",id++);
		x.out();
	}	
}



void add(char *s){
	size_t i,slot;
	std::vector<int> slots;
	for(i=0;i<4;i++,s+=2) if(*s != '0'){
		slot = (*s - 'A') << 1;
		slot |= *(s+1) == '-';
		//printf("%s : %d %d\n",s,id,slot);
		slots.push_back(slot);
	}
	if(slots.size() > 1){
		for(i=0; i<slots.size(); i++) {
			pool.insert(Block(slots,i));
		}
	}
}

void build(){
	int id=0;
	for(auto x : pool){
		blocks.push_back(x);
		nodes[x.in].insert(id++);
	}
}

void read(int n){
	int i;
	char s[11];
	for(i=0;i<52;i++) nodes[i].clear();
	pool.clear();
	blocks.clear();
	for(i=0;i<n;i++){
		scanf("%s",s);
		add(s);
	}	
	build();
	//dout();
}

bool dfu(Block &u){
	u.vis = 1;
	//u.out();
	for(auto x : u.outs) {
		for(auto v : nodes[x]){
			auto it = blocks.begin() + v;
			if(it->vis == 1) return false;
			if(it->vis == 0) dfu(*it);
		}
	}
	u.vis = 2;
	return true;
}

bool dfs(){	
	for(auto x : blocks) if(x.vis == false){
		if(!dfu(x)) return false;
	}
	return true;
}

int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		read(n);
		fprintf(stderr,"%llu\n",blocks.size());
		puts(dfs()?"bounded":"unbounded");
	}
	return 0;
}
