#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned int uint;

void d2b(uint x,int n){
	if(n==0) return;
	d2b(x>>1,n-1);
	putchar(x&1?'1':'0');
}

struct bitmap{
	uint bits[5];
	
	bitmap(){ 
		memset(bits,0,sizeof(bits)); 
	};
	bitmap(const bitmap &rhs){
		memcpy(bits,rhs.bits,sizeof(bits));
	}

	inline void set(int id,uint val){
		bits[id] = val;
	}	

	inline bitmap & operator<<=(const size_t n){
		for(int i =0;i<5;i++) bits[i] <<= n;
		return *this;
	}

	inline bitmap & operator>>=(const size_t n){
		for(int i =0;i<5;i++) bits[i] >>= n;
		return *this;
	}
	inline bitmap & operator |= (const bitmap &rhs){
		for(int i =0;i<5;i++) bits[i] |= rhs.bits[i];
		return *this;
	}
	inline bool conflict(const bitmap &rhs){
		for(int i = 0 ; i <  5; i++) if(bits[i] & rhs.bits[i]) return true;
		return false;
	}
	inline void out(){
		puts("----------------");
		for(int i =0 ;i< 5;i++) printf("%08x:",bits[i]),d2b(bits[i],32),putchar('\n');
	}
};

uint ans;
bitmap task;
std::vector<uint> legal;

inline void init(bitmap &task,uint n){
	bitmap t(task);
	legal.clear();
	for(uint i=0;i<=n;i++,t>>=1) if(!task.conflict(t)) legal.push_back(i); 	
}

void dfs(bitmap &cpu,uint k,uint len){
	if(len + legal[0] * (10 - k) >= ans) return;
	if(k==10u) {
		if(ans > len) ans = len;
		return;
	}	

	for(auto i : legal) {
		bitmap t(task);
		t >>= i;
		if(!cpu.conflict(t)){
			bitmap v(cpu);
			v <<= i;
			v |= task;
			dfs(v,k+1,len+i); 
		}
	}	
}

inline uint get(char *s){
	uint r = 0;
	while(*s){
		r <<=1;
		r |= *s == 'X';
		s++;
	}
	return r;
}

int main(){
	int i,n;
	
	char s[22];
	while(scanf("%d",&n),n){		
		for(i=0;i<5;i++){
			scanf("%s",s);
			task.set(i,get(s));
		}
		
		init(task,n);
		bitmap cpu(task);
		ans = 10*n;
		dfs(cpu,1,n);
		printf("%d\n",ans);
	}
	return 0;
}