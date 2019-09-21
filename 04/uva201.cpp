#include <cstdio>
#include <list>
#include <vector>
#include <utility>
#include <cstring>

const unsigned int maxn = 17;

class BIT{
private:
	int a[maxn];
	int n;
	inline int lowbit(int x) { return x & -x ;}
	int _query(int pos){
		int i,s=0;
		for(i=pos;i>0;i-=lowbit(i)) s += a[i];
		return s;
	}
public:
	BIT(int n):n(n){ 
		memset(a,0,sizeof(int)*(n+1));
	};
	void update(int pos,int delta){
		int i;
		for(i=pos;i<=n;i+=lowbit(i)) a[i]+=delta;
	}
	int query(int left,int right){
		return _query(right) - _query(left - 1);
	}
	void out(){
		for(int i=1;i<=n;i++) printf("%d%c",a[i],",\n"[i==n]);
	}
};

int main(){
	int n,m,x,y,i,j,T=0;
	char c;
	while(scanf("%d",&n)!=EOF){
		if(T) puts("\n**********************************\n");
		scanf("%d",&m);
		std::list<std::pair<int,int> > sp;
		int tag[n+1][n+1]={0},ans[n+1]={0},flag=0;
		std::vector<BIT> H(n+1,BIT(n-1)),V(n+1,BIT(n-1));
		
		for(i=0;i<m;i++){
			scanf(" %c %d %d",&c,&x,&y);
			if(c=='H'){
				H[x].update(y,1);
				tag[x][y]++;
			} else {
				V[x].update(y,1);
				tag[y][x]++; 
			}
		}
		for(i=1;i<=n;i++) for(j=1;j<=n;j++) if(tag[i][j]==2) sp.emplace_back(i,j);

		//for(i=1;i<=n;i++) H[i].out();
		//puts("-----------------------");
		//for(i=1;i<=n;i++) V[i].out();

		for(i=0;i<n;i++){
			for(auto isp = sp.begin(); isp != sp.end();){
				x = isp->first;
				y = isp->second;
				//printf("%d %d %d ",i+1,x,y);
				if(y+i<n && x+i < n){
					if(H[x].query(y,y+i)==i+1 && V[y].query(x,x+i) == i+1){
						if(H[x+i+1].query(y,y+i)==i+1 && V[y+i+1].query(x,x+i) == i+1){
							ans[i]++;
							flag = 1;
						}
						isp++;
					} else {
						isp = sp.erase(isp);
					}					
				} else {
					isp = sp.erase(isp);
				}
				//printf("%d\n",ans[i]);
			}
		}
		printf("Problem #%d\n\n",++T);
		if(flag) {
			for(i=0;i<n;i++) if(ans[i]) printf("%d square (s) of size %d\n",ans[i],i+1);
		} else 
			puts("No completed squares can be found.");
		
	}
}
