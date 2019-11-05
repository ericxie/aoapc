#include <cstdio>

struct dlink{
	struct node{
		struct node *link[2];
	};
	node *v;
	int n,dir;
#define prev dir
#define next dir^1
	dlink(int n):n(n),dir(0){
		v = new node[n+2];
		v[0].link[next] = v + 1;
		v[0].link[prev]  = NULL;
		v[n+1].link[prev] = v+n;
		v[n+1].link[next] = NULL;
		for(int i=1;i<=n;i++){
			v[i].link[prev] = v+i-1;
			v[i].link[next] = v+i+1;
		}
	}
	~dlink() { delete[] v; }
	
	inline void link(node *p,node *q){
		p->link[next] = q;
		q->link[prev] = p;
	}

	inline node *move(int x){
		node *px = v + x;
		node *prev_x = px->link[prev];
		node *next_x = px->link[next];
		link(prev_x,next_x);
		return px;
	}
	inline void before(int x,int y){
		node *px = move(x);
		node *py = v + y;
		node *prev_y = py->link[prev];
		link(prev_y,px);
		link(px,py);
	}
	inline void after(int x,int y){
		node *px = move(x);
		node *py = v+y;
		node *next_y = py->link[next];
		link(py,px);
		link(px,next_y);
	}
	inline void swap(int x,int y){
		node * px = v + x;
		node * prev_x = px->link[prev];
		node * next_x = px->link[next];
		node * py = v + y;
		node * prev_y = py->link[prev];
		node * next_y = py->link[next];
		if(px == prev_y){
			link(prev_x,py);
			link(py,px);
			link(px,next_y);
		} else if( px == next_y){
			link(prev_y,px);
			link(px,py);
			link(py,next_x);
		} else {
			link(prev_x,py);
			link(py,next_x);
			link(prev_y,px);
			link(px,next_y);	
		}		
	}
	inline void reverse(){
		dir ^= 1;
	}
	void prt(){
		node *p;
		if(dir) p = v[n+1].link[next];
		else p = v[0].link[next];
		while(p->link[next]){
			printf("%lld ", p - v);
			p = p->link[next];
		}
		putchar('\n');
	}
	long long out(){
		node *p;
		int t = 1;
		if(dir) p = v[n+1].link[next];
		else p = v[0].link[next];
		long long ans = 0;
		while(p->link[next]){
			if(t) ans += p - v;
			t ^= 1;
			p = p->link[next];
		} 
		return ans;
	}
#undef prev
#undef next
};

int main(){
	int n,m,k,x,y,T=0;
	while(scanf("%d %d",&n,&m)!=EOF){
		dlink a(n);
		while(m--){
			scanf("%d",&k);
			if(k==4) a.reverse();
			else {
				scanf("%d %d",&x,&y);
				switch(k){
					case 1: a.before(x,y);	break;
					case 2: a.after(x,y);	break;
					case 3: a.swap(x,y);	break;
				}
			}
			//a.prt();
		}
		printf("Case %d: %lld\n",++T,a.out());
	}
	return 0;
}