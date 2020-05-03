#include <cstdio>
#include <unordered_map>
#include <vector>

struct _T{
	std::unordered_map<int,int> input;
	std::unordered_map<int,int> output;	
};

std::vector<int> P;
std::vector<_T> T;
int turns,np,nt;

bool read(){
	P.clear();
	T.clear();
	int i;
	scanf("%d",&np);
	if(np == 0) return false;
	P.resize(np);
	for(i=0;i<np;i++) scanf("%d",&P[i]);
	
	scanf("%d",&nt);
	T.resize(nt);
	for(i=0;i<nt;i++){
		int t;
		while(scanf("%d",&t),t){
			if(t<0)	T[i].input[-t-1]++;
			else 	T[i].output[t-1]++;	
		}		
	}
	scanf("%d",&turns);
	return true;
}

inline bool ok(const _T &a){
	for(auto x : a.input){
		if(P[x.first] < x.second) return false;
	}
	return true;
}

inline void fire(const _T &a){
	for(auto x : a.input) P[x.first] -= x.second;
	for(auto x : a.output) P[x.first] += x.second;
}

void simulate(int cas){
	int i,cnt=0,flag;
	while(cnt < turns){
		flag = 0;
		for(auto &x : T){
			if(ok(x)){
				flag = 1;
				cnt++;
				fire(x);
				if(cnt == turns) goto end;
			}
		}
		if(!flag) break;
	}
end:
	printf("Case %d: %s after %d transitions\n",cas,cnt<turns?"dead":"still live",cnt);
	printf("Places with tokens:");
	for(i=0;i<P.size();i++) if(P[i]){
		printf(" %d (%d)",i+1,P[i]);
	}
	puts("\n");
}

int main(){
	int T = 0;
	while(read()){
		simulate(++T);
	}
	return 0;
}