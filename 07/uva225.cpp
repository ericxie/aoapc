#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <utility>
std::unordered_map<int,std::vector<int> > X;
std::unordered_map<int,std::vector<int> > Y;

void add(std::unordered_map<int,std::vector<int> > &hash,int key,int value){
	auto it = hash.find(key);
	if(it == hash.end()){
		std::vector<int> t;
		t.push_back(value);
		hash.emplace(key,t);
	} else {
		it->second.push_back(value);
	}
}

bool vis[222][222];
const int offset = 111;
char s[22];

//ensw
const int dx[]={1,0,0,-1};
const int dy[]={0,1,-1,0};
const char op[]={'e','n','s','w'};
const int mask[]={6,9,9,6};
int cnt;


inline bool _check(const std::unordered_map<int,std::vector<int> > &hash,int key,int low,int upp){
	auto it = hash.find(key);
	if(it == hash.end()) return true;
	for(auto x : it->second) if(low <=x && x <= upp) return false;
	return true;
}

inline bool check(int d,int x,int y,int nx,int ny){
	if(vis[nx+offset][ny+offset]) return false;
	if(d == 0) return _check(Y,y,x,nx);
	if(d == 1) return _check(X,x,y,ny);
	if(d == 2) return _check(X,x,ny,y);
	if(d == 3) return _check(Y,y,nx,x);
	return false;
}

inline bool cut(int n,int k,int d,int x,int y){
	if(d == 1 || d == 2) std::swap(x,y);
	if(x<0) x = -x;
	if(y<0) y = -y;
	if((k & 1) == (n & 1)){
		if((x << 2) > (n+k)*(n-k+2)) return true;
		if((y << 2) > n*n - k*k) return true;
	} else {
		if((x << 2) > (n-k+1)*(n+k-1)) return true;
		if((y << 2) > (n+k+1)*(n-k+1)) return true;
	}
	return false;	
}

void dfs(int n,int k,int d,int x,int y){
	if(k==n){
		if(x==0 && y==0){
			puts(s);
			cnt++;	
		}		
		return;
	}	
	//fprintf(stderr,"%d %d %x %d %d\n",n,k,d,x,y);	
	for(int i=0;i<4;i++) if(d & (1<<i)){
		if(cut(n,k+1,i,x,y)) break;		
		int nx,ny;
		nx = dx[i] * (k+1) + x;
		ny = dy[i] * (k+1) + y;
		if(check(i,x,y,nx,ny)){
			s[k] = op[i];
			//fprintf(stderr,"%*c-%c->(%d,%d)\n",k*4,' ',s[k],nx,ny);
			vis[nx+offset][ny+offset] = true;
			dfs(n,k+1,mask[i],nx,ny);
			vis[nx+offset][ny+offset] = false;
		}		
	}	
}

int main(){
	int T;
	//freopen("225.log","w",stderr);
	scanf("%d",&T);
	while(T--){
		int n,m,i,x,y;
		scanf("%d %d",&n,&m);	
		if(n==7 || n == 8 || n==15 || n==16){
			X.clear();
			Y.clear();
			for(i=0;i<m;i++){
				scanf("%d %d",&x,&y);
				add(X,x,y);
				add(Y,y,x);
			}
			cnt = 0;
			memset(vis,0,sizeof(vis));		
			s[n] = 0;
			dfs(n,0,15,0,0);
			printf("Found %d golygon(s).\n\n",cnt);	
		} else {
			for(i=0;i<m;i++) scanf("%d %d",&x,&y);
			printf("Found 0 golygon(s).\n\n");	
		}	
				
		
	}
	return 0;
}

