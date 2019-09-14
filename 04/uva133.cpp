#include <cstdio>
#define N 20
struct node{
	int val,L,R;
}Q[N];

void init(int n){
	int i;
	for(i=0;i<n;i++) {
		Q[i].val = i+1;
		Q[i].L = (i-1+n)%n;
		Q[i].R = (i+1+n)%n;
	} 
}

void del(int idx){	
	Q[Q[idx].L].R = Q[idx].R;
	Q[Q[idx].R].L = Q[idx].L;
}

int main(){
	int n,k,m,p,q,i;
	while(scanf("%d %d %d",&n,&k,&m),n){
		init(n);
		p = 0,q = n-1;
		while(n){
			for(i=1;i<k;i++) p = Q[p].R;
			for(i=1;i<m;i++) q = Q[q].L;
			if(p==q) {
				printf("%3d",Q[p].val);
				del(p);	
				p = Q[p].R;	
				q = Q[q].L;
				n--;						
			}
			else {
				printf("%3d%3d",Q[p].val,Q[q].val);
				del(p);
				del(q);
				if(Q[p].R != q) p = Q[p].R, q = Q[q].L;
				else p = Q[q].R, q = Q[p].L;
				n-=2;				
			}
			
			if(n) putchar(',');
		}
		putchar('\n');
	}
	return 0;
}