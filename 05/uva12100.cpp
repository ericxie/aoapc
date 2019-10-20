#include <cstdio>
#include <queue>
#include <cstring>

int w[10];

struct node{
	int w,id;
	node(int w,int id):w(w),id(id){};
	node():w(0),id(0){}
	void out(){
		printf("%d %d\n",w,id);
	}
}Q[11111];

int head,tail;


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int i,n,id,t;
		memset(w,0,sizeof(w));
		head = tail = 0;
		scanf("%d %d",&n,&id);
		for(i=0;i<n;i++){
			scanf("%d",&t);
			w[t]++;
			Q[tail++] = node(t,i);
		}
		
		
		int k,ans=0;
		for(i=9;i>0 && w[i]==0;i--);
		k = i;
		
		for(;;){
			node x = Q[head++];
			//x.out();
			if(x.w < k){
				Q[tail++] = x;
			} else {
				ans++;
				if(x.id == id) {
					printf("%d\n",ans);
					break;
				} 
				w[k]--;
				while(w[k]==0) k--; 
			}
		}
	}
	return 0;
}