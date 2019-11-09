#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 11111;
const int inf = 1e8;

struct bst{
	struct node{
		int v,leaf,sum,left,right;
		node():v(0),leaf(0),sum(0),left(0),right(0){};
	};
	node tree[N];
	int last;

	int _build(int *inord,int *postord,int n){
		int i,rt;
		rt = last;
		tree[rt].leaf = tree[rt].sum = tree[rt].v = postord[n-1];
		last++;
		if(n > 1) {
			int ls=inf,rs=inf;
			for(i=0;i<n && inord[i] != postord[n-1]; i++);
			if(i>0) {
				tree[rt].left = _build(inord,postord,i);
				ls = tree[tree[rt].left].sum;
			}
			if(i<n-1){
				tree[rt].right = _build(inord+i+1,postord+i,n-i-1);
				rs = tree[tree[rt].right].sum; 
			}
			tree[rt].sum += std::min(ls,rs);
			if(ls < rs){
				tree[rt].leaf = tree[tree[rt].left].leaf;
			} else if(ls > rs){
				tree[rt].leaf = tree[tree[rt].right].leaf;
			} else {
				tree[rt].leaf = std::min(tree[tree[rt].left].leaf,tree[tree[rt].right].leaf);
			}
		}		
		return rt;
	}
	bst(int *inord,int *postord,int n):last(1){
		_build(inord,postord,n);
	}
	inline int solve(){
		return tree[1].leaf;
	}
};

int main(){
	int inord[N],postord[N],n,i;
	char buf[N*5],*p;
	
	while(gets(buf)){
		n = 0;
		p = strtok(buf," ");
		while(p){
			sscanf(p,"%d",inord+n);
			n++;
			p = strtok(0," ");	
		}
		for(i=0;i<n;i++) scanf("%d",postord+i);
		getchar();
		bst a(inord,postord,n);
		printf("%d\n",a.solve());	
	}
	return 0;
}

