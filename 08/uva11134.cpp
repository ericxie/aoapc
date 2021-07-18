#include <cstdio>
#include <vector>
#include <algorithm>

struct node{
	int id,left,right,tag;
	node()=default;
	node(int _id,int _left,int _right):id(_id),left(_left),right(_right){ tag = 0; }
	bool operator < (const node &rhs) const{
		if(right == rhs.right) return left < rhs.left;
		return right < rhs.right;
	}	
};

bool set(std::vector<node> &x,std::vector<int> &ax){
	int n = x.size();
	for(int i = 1; i<= n; i++){
		int flag = 0;
		//fprintf(stderr,"i : %d\n",i);
		for(auto &u : x){
			//fprintf(stderr,"%d: %d %d %d\n",u.id,u.tag,u.left,u.right);
			if(u.tag) continue;
			if(u.right < i) break;
			if(u.left <= i && i<= u.right){
				u.tag = 1;
				flag = 1;
				ax[u.id] = i;
				break;
			}
		}
		if(!flag) return false;
	}
	return true;
}

int main(){
	int n;
	while(scanf("%d",&n),n){
		std::vector<node> x;
		std::vector<node> y;
		std::vector<int> ax(n),ay(n);
		for(int i = 0 ;i < n ; i++){
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			x.emplace_back(i,x1,x2);
			y.emplace_back(i,y1,y2);
		}
		std::sort(x.begin(),x.end());
		std::sort(y.begin(),y.end());	
		//for(auto u : x) fprintf(stderr,"x , %d : %d %d\n",u.id,u.left,u.right);	
		//for(auto u : y) fprintf(stderr,"y , %d : %d %d\n",u.id,u.left,u.right);	
		if(set(x,ax) && set(y,ay)){			
			for(int i = 0; i < n; i++) printf("%d %d\n",ax[i],ay[i]);
		} else {
			puts("IMPOSSIBLE");
		}	
	}
	return 0;
}