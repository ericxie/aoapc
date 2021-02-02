#include <cstdio>
#include <list>

char mat[22][22];
int n;
struct node{
	int x,y,cnt;
};

node leader[26];

struct cover{
	int id,x,y,h,w;
	cover() = default;
	cover(int _id,int _x,int _y,int _h,int _w):id(_id),x(_x),y(_y),h(_h),w(_w){};
};

std::list<cover> pos[22][22];

inline int check(int x,int y,int h,int w){
	
	for(int i=0; i<h; i++) for(int j = 0; j<w; j++) {
		//fprintf(stderr,"check: %d %d : %c\n",x+i,y+j,mat[x+i][y+j]);
		if(x+i < 0 || x+i >=n || y+j< 0 || y+j >=n) return 0;
		if(mat[x+i][y+j] != '.') return 0;
	}
	return 1;
}

inline void add(int id,int x,int y,int h,int w){
	for(int i=0; i<h; i++) for(int j = 0; j<w; j++) pos[x+i][y+j].emplace_back(id,x,y,h,w);
}

inline void init(int sz){
	int i,j,k,h,w,x,y,cnt;
	for(i = 0; i<n; i++) for(j=0; j<n; j++) pos[i][j].clear();
	for(k=0;k<sz;k++){
		x = leader[k].x;
		y = leader[k].y;
		cnt = leader[k].cnt;
		//fprintf(stderr,"%d %d %d\n",x,y,cnt);
		mat[x][y] = '.';
		for(h=1;h<=cnt;h++) if(cnt % h == 0){
			w = cnt / h;
			//fprintf(stderr,"  h=%d,w=%d\n",h,w);
			for(i=0;i<h;i++) for(j=0;j<w;j++) {	
				//fprintf(stderr,"   %d %d %d %d:",x-i,y-j,h,w);			
				if(check(x-i,y-j,h,w)){
					//fprintf(stderr,"1\n");	
					add(k,x-i,y-j,h,w);
				} //else 	fprintf(stderr,"0\n");				
			}
		}
		mat[x][y] = '0' + cnt;
	}
	//for(i=0;i<n;i++) for(j=0;j<n;j++) {
	//	fprintf(stderr,"%d %d :\n", i,j);
	//	for(auto u : pos[i][j]){
	//		fprintf(stderr,"  %d %d %d %d %d\n",u.id,u.x,u.y,u.h,u.w);
	//	}
	//}
}

inline void update(int x,int y,int h,int w,char c){
	for(int i=0; i<h; i++) for(int j = 0; j<w; j++) mat[x+i][y+j]= c;
}

inline void out(FILE *fp){
	for(int i=0;i<n;i++) fprintf(fp,"%s\n",mat[i]);
}

int dfs(int k,int mask,char c){
	int nn = n*n,x,y;
	if(k == nn) return 1;	
	
	while(k<nn){
		x = k / n;
		y = k % n;
		if(mat[x][y]>='A' && mat[x][y]<='Z') k++;
		else break;
	}
	if(k == nn) return 1;
	//fprintf(stderr,"- %d %d : ",x,y);
	for(auto u : pos[x][y]) {
		if(mask & (1 << u.id)) continue;
		//fprintf(stderr,"   =%d %d %d %d %d\n",u.id,u.x,u.y,u.h,u.w);
		mat[leader[u.id].x][leader[u.id].y] = '.';
		if(check(u.x,u.y,u.h,u.w)){
			update(u.x,u.y,u.h,u.w,c);
			//out(stderr);
			if(dfs(k+1,mask | (1<<u.id),c+1)) return 1;
			update(u.x,u.y,u.h,u.w,'.');
		}
		mat[leader[u.id].x][leader[u.id].y] = leader[u.id].cnt;

	}
	return 0;
}

int main(){
	int sz,k;
	//freopen("11846.log","w",stderr);
	while(scanf("%d %d",&n,&sz),n){
		k=0;
		for(int i=0;i<n;i++) {
			scanf("%s",mat[i]);			
			for(int j = 0; j<n; j++) if(mat[i][j]!='.'){
				leader[k].x = i;
				leader[k].y = j;
				leader[k].cnt = mat[i][j] - '0';
				//fprintf(stderr,"+%d: %d %d %d\n",k,i,j,mat[i][j] - '0');
				k++;
			}			
		}
		init(sz);
		if(dfs(0,0,'A')){
			out(stdout);
		} else {
			puts("IMPOSSIBLE");
		}
	}
	return 0;
}