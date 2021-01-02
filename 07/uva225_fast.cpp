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
std::array<int,16> s;

//ensw
const int dx[]={1,0,0,-1};
const int dy[]={0,1,-1,0};
const char op[]={'e','n','s','w'};
const int mask[]={6,9,9,6};
const int num[4]={7,8,15,16};

std::vector<std::array<int,16> > ans[4];
int id;


inline bool _check(const std::unordered_map<int,std::vector<int> > &hash,int key,int low,int upp){
	auto it = hash.find(key);
	if(it == hash.end()) return true;
	for(auto x : it->second) if(low <=x && x <= upp) return false;
	return true;
}

inline bool check(int d,int x,int y,int nx,int ny){	
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
			ans[id].push_back(s);
		}		
		return;
	}	
	//fprintf(stderr,"%d %d %x %d %d\n",n,k,d,x,y);	
	for(int i=0;i<4;i++) if(d & (1<<i)){
		if(cut(n,k+1,i,x,y)) break;		
		int nx,ny;
		nx = dx[i] * (k+1) + x;
		ny = dy[i] * (k+1) + y;
		if(!vis[nx+offset][ny+offset]){
			s[k] = i;
			//fprintf(stderr,"%*c-%c->(%d,%d)\n",k*4,' ',s[k],nx,ny);
			vis[nx+offset][ny+offset] = true;
			dfs(n,k+1,mask[i],nx,ny);
			vis[nx+offset][ny+offset] = false;
		}		
	}	
}

void init(){
	for(int i=0;i<4;i++){
		id = i;
		memset(vis,0,sizeof(vis));
		dfs(num[i],0,15,0,0);
	}	
}

void solve(int n,int k){
	int i,x,y,nx,ny,cnt=0;
	for(auto t : ans[k]){
		x = 0 , y = 0;
		for(i = 0; i<n; i++){
			nx = x + dx[t[i]] * (i+1);
			ny = y + dy[t[i]] * (i+1);
			if(!check(t[i],x,y,nx,ny)) goto next;
			x = nx, y = ny;
		}
		for(i=0;i<n;i++) putchar(op[t[i]]);
		putchar('\n');
		cnt++;
		next: ;
	}
	printf("Found %d golygon(s).\n\n",cnt);	
}

int main(){
	int T;
	//freopen("225.log","w",stderr);
	scanf("%d",&T);
	init();
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
			for(i=0;i<4;i++) if(num[i] == n){
				solve(n,i);
				break;
			}
		} else {
			for(i=0;i<m;i++) scanf("%d %d",&x,&y);
			printf("Found 0 golygon(s).\n\n");	
		}	
				
		
	}
	return 0;
}

