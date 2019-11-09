#include <cstdio>
#include <cstring>

typedef unsigned int uint;
const int N = 32;
struct graph{
	uint g[N];
	inline int popcount(){
		int s = 0;
		for(int i=0;i<N;i++) s+=__builtin_popcount(g[i]);
		return s;
	}
	inline void set(int x,int y,int w){
		for(int i=0;i<w;i++) {
			g[x+i] |= (~0u >> (32-w)) << y;
		}
	}
	void draw(int x,int y,int w){
		if(w == 0) return;
		char c = getchar();
		int w1 = w >> 1;
		if(c=='f') set(x,y,w);
		else if(c=='p'){
			draw(x,y,w1);
			draw(x,y+w1,w1);
			draw(x+w1,y+w1,w1);
			draw(x+w1,y,w1);
		}
	}	
	
	graph(){ 
		memset(g,0,sizeof(g)); 
	}	
};

int main(){
	int T;
	scanf("%d ",&T);
	while(T--){
		graph a;
		a.draw(0,0,32);
		getchar();
		a.draw(0,0,32);
		getchar();
		printf("There are %d black pixels.\n",a.popcount());	
	}	
	return 0;
}