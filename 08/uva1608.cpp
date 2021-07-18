#include <cstdio>
#include <unordered_map>

const int N = 2e5+5;

int a[N];
int left[N],right[N];
std::unordered_map<int,int> pos;

bool judge(int p,int q){
	int i,len,j;
	if(p >= q) return 1;
	len = (q - p) >> 1;  
	for(i=0;i<=len;i++){
		j = p+i;
		if(left[j] < p && right[j] > q) return judge(p,j-1) && judge(j+1,q);
		j = q-i;
		if(left[j] < p && right[j] > q) return judge(p,j-1) && judge(j+1,q);
	}
	return 0;
}

int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",a+i);
		pos.clear();
		for(int i=0;i<n;i++){
			auto it = pos.find(a[i]);
			if(it == pos.end()) {
				left[i] = -1;
				pos.emplace(a[i],i);
			} else {
				left[i] = it->second;
				it->second = i;
			}			
		}
		
		pos.clear();
		for(int i=n-1;i>=0;i--){
			auto it = pos.find(a[i]);
			if(it == pos.end()) {
				right[i] = n;
				pos.emplace(a[i],i);
			} else {
				right[i] = it->second;
				it->second = i;
			}
		}
		// for(int i = 0; i<n; i++) printf("%2d ",left[i]);
		// puts("");
		// for(int i = 0; i<n; i++) printf("%2d ",right[i]);
		// puts("");
		puts(judge(0,n-1)?"non-boring":"boring");
	}
	return 0;
}