#include <cstdio>
#include <cstdlib>
#include <cstring>
#define HS 10000037

struct _node{
	int key,value,next;
};
struct Hash{
	int head[HS];
	_node node[HS<<4];
	int cnt;
	Hash(){cnt = 0;}

	inline int id(int x) { return (x % HS + HS) % HS; }

	inline int insert(int x){
		int hx = id(x);
		int p = head[hx];
		//fprintf(stderr,"insert : %d %d %d\n",x,hx,p);
		while(p!=-1){
			if(node[p].key == x) {
				node[p].value++;
				return 0;
			}
			p = node[p].next; 
		}
		node[cnt].key = x;
		node[cnt].value = 1;

		node[cnt].next = head[hx];
		head[hx] = cnt++;
		return 1;
	}
	inline int find(int x,int &value){
		int hx =  id(x);
		int p = head[hx];
		while(p != -1){
			if(node[p].key == x) {
				value = node[p].value;
				return 1;
			}
			p = node[p].next;
		}
		return 0;
	}
	inline void clear(){
		cnt = 0;
		memset(head,-1,sizeof(head));
	}	
};

Hash hash; 
int a[4000],b[4000],c[4000],d[4000];

int main(){
	int T,n,i,j,ans,t,v;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		hash.clear();
		
		for(i=0;i<n;i++) scanf("%d %d %d %d",a+i,b+i,c+i,d+i);
		for(i=0;i<n;i++) for(j=0;j<n;j++){
			t = a[i] + b[j];
			hash.insert(t);	
		}
		//fprintf(stderr,"cnt:%d\n",hash.cnt);
		//for(i=0;i<hash.cnt;i++) fprintf(stderr,"%d %d %d\n",hash.node[i].key,hash.node[i].value,hash.node[i].next);
		ans = 0;
		for(i=0;i<n;i++) for(j=0;j<n;j++){
			t = -(c[i] + d[j]);
			if(hash.find(t,v)) ans += v;
		}		
		printf("%d\n",ans);

		if(T) putchar('\n');
	}
	return 0;
}