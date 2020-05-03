#include <cstdio>
#include <set>
#include <cstring>

int mat[64][64];
std::set<int> seq;

inline int get(int x,int y,int sz){
	int i,j,tag;
	tag = mat[x][y];
	for(i=0;i<sz;i++) for(j=0;j<sz;j++){
		if(tag != mat[x+i][y+j]) return -1;
	}
	return tag;
}

void encode(int x,int y,int sz,int k,int r){	
	int i,n=sz>>1,t,dx,dy;	
	t = get(x,y,sz);
	if(t == 1) seq.insert(r);
	else if(t == 0) return;
	else {
		if(n == 0) return;
		for(i=0;i<4;i++) {
			dx = x+(i>>1)*n;
			dy = y+(i&1)*n;
			encode(dx,dy,n,k*5,k*(i+1)+r);
		}	
	}	
}

inline void seq_out(){
	int cnt = 0;
	for(auto x : seq){
		if(cnt) putchar(' ');
		printf("%d",x); 	
		if(++cnt == 12) putchar('\n'),cnt=0;
	}
	if(cnt) putchar('\n');
	printf("Total number of black nodes = %llu\n",seq.size());
}

inline void set(int x,int y,int sz){
	for(int i=x;i<x+sz;i++) for(int j=y;j<y+sz;j++) mat[i][j] = 1;
}


void decode(int x,int y,int sz,int k){
	if(k==0) {
		set(x,y,sz);
		return;
	}
	int n = sz >> 1;
	int dx,dy,p;
	p = k%5 - 1;
	dx = x + (p>>1) * n;
	dy = y + (p&1) * n;
	if(k<5) set(dx,dy,n);
	else decode(dx,dy,n,k/5);
}

inline void mat_out(int sz){
	for(int i=0;i<sz;i++){
		for(int j=0;j<sz;j++) putchar(mat[i][j]?'*':'.');
		putchar('\n');
	}
}


int main(){
	int sz,i,j,k=0;
	while(scanf("%d",&sz),sz){
		if(k) putchar('\n');
		printf("Image %d\n",++k);
		if(sz>0){
			for(i=0;i<sz;i++) for(j=0;j<sz;j++) scanf("%1d",&mat[i][j]);
			seq.clear();
			encode(0,0,sz,1,0);
			seq_out();	
		} else {
			sz = -sz;
			int t;
			memset(mat,0,sizeof(mat));
			while(scanf("%d",&t),t!=-1){
				decode(0,0,sz,t);
			}
			mat_out(sz);
		}		
	}
	return 0;
}
