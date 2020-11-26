#include <cstdio>
#include <vector>
#include <cstring>

long long grid[5][55];
int cnt[5];

inline int x2id(int x,int y,int n) { return (n + n + 1) * x + y;}
inline int y2id(int x,int y,int n) { return (n + n + 1) * x + n + y;}

std::vector<int> grids[5][55];		// grids[width][grid]
std::vector<int> edges[5][60]; 		// edges[width][edge]

const int numGrids[5] = {1,5,14,30,55};
const int numEdges[5] = {4,12,24,40,60}; 
int fullsz[5][55];
int currsz[5][55];

inline void addEdge(int n,int w,int x,int y,int k){
	int i;
	for(i=0;i<w;i++) {
		grids[n][k].push_back(x2id(x,y+i,n+1));		
		grids[n][k].push_back(y2id(x+i,y,n+1));
		grids[n][k].push_back(y2id(x+i,y+w,n+1));
		grids[n][k].push_back(x2id(x+w,y+i,n+1));
		fullsz[n][k] += 4;
	}
	//fprintf(stderr,"%d %d %d %d,%d: ",n,w,x,y,k);
	//for(i=0;i<fullsz[n][k];i++) fprintf(stderr,"%d%c",grids[n][k][i],",\n"[i==fullsz[n][k]-1]);
}

inline void gridEdge(){
	int n,w,x,y,k;
	for(n=0;n<5;n++){
		k = 0;
		for(w=1;w<=n+1;w++){			
			for(x=0;x<=n+1-w;x++)
				for(y=0;y<=n+1-w;y++)	
					addEdge(n,w,x,y,k++);											
		}
	}
}

inline void edgeGrid(){
	int n,i,sz;
	for(n=0;n<5;n++){
		sz = numGrids[n];
		//fprintf(stderr,"size = %d , sz = %d\n",n+1,sz);
		for(i=0;i<sz;i++){			
			for(int eid : grids[n][i]){
				//fprintf(stderr,"%d %d : %d\n",n,i,eid);
				edges[n][eid].push_back(i);
			}
		}
		
		// for(i=0;i<numEdges[n];i++){
		// 	fprintf(stderr,"%d :",i);
		// 	for(auto x : edges[n][i]) fprintf(stderr," %d",x);
		// 	fprintf(stderr,"\n");
		// }
	}
}

inline void del(int n,int &h,int eid){
	for(int x : edges[n][eid]){
		//fprintf(stderr,"del: %d ,currsz = %d, fullsz= %d, h = %d;",x,currsz[n][x],fullsz[n][x],h);
		if(currsz[n][x] == fullsz[n][x]) h--;
		currsz[n][x]--; 
		//fprintf(stderr,"after : h = %d, currsz = %d\n",h,currsz[n][x]); 
	}
}

inline void add(int n,int &h,int eid){
	for(int x : edges[n][eid]){	
		//fprintf(stderr,"add: %d ,currsz = %d, fullsz= %d, h = %d;",x,currsz[n][x],fullsz[n][x],h);	
		currsz[n][x]++; 
		if(currsz[n][x] == fullsz[n][x]) h++;
		//fprintf(stderr,"after : h = %d, currsz = %d\n",h,currsz[n][x]); 
	}
}

inline int findGrid(int n){
	int i;
	for(i=0;i<numGrids[n];i++) if(currsz[n][i] == fullsz[n][i]) return i;
	return -1;
}

bool dfs(int maxd,int d,int n,int h){
	//fprintf(stderr,"%d %d %d %d\n",maxd,d,n,h);
	if(h==0) return true;
	if(maxd == d) return false;
	int gid = findGrid(n);
	//fprintf(stderr,"gid : %d\n",gid);
	if(gid == -1) return true;
	
	for(int i=0; i< fullsz[n][gid]; i++){
		del(n,h,grids[n][gid][i]);
		//fprintf(stderr,"eid : %d, del : %d\n",grids[n][gid][i],h);
		if(dfs(maxd,d+1,n,h)) return true;
		add(n,h,grids[n][gid][i]);
		//fprintf(stderr,"add : %d\n",h);
	}
	return false;
}

int ida(int n,int h){
	int d;
	for(d = (h+n)/(n+1);d <= numGrids[n]; d++ ){
		if(dfs(d,0,n,h)) return d;
	}
	return -1;
}

int main(){
	int T,sz,i,n,h,t;
	
	gridEdge();
	edgeGrid();
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&sz,&n);
		sz--;
		h = numGrids[sz];
		for(i=0;i<h;i++) currsz[sz][i] = fullsz[sz][i];	
		for(i=0;i<n;i++) {
			scanf("%d",&t);
			del(sz,h,t-1);			
		}
		printf("%d\n",ida(sz,h));
	}
	return 0;
}