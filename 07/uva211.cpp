#include <cstdio>
#include <cstring>
#include <algorithm>

int g[7][8];
int ans[7][8];
int cnt;

const int ids[]={1,8,14,19,23,26,28};

inline int ID(int a,int b){
	if(a > b) std::swap(a,b);
	return ids[a] + b - a;
}

void out(FILE *fp,int (*p)[8]){
	for(int i = 0; i< 7;i++) {
		for(int j=0;j<8;j++) fprintf(fp,"%4d",p[i][j]);
		fputc('\n',fp);
	}
	fputc('\n',fp);
}

void dfs(int x,int y,int mask){
	if(x==7){
		out(stdout,ans);
		cnt++;
		return;
	}
	if(ans[x][y]){
		if(y==7) dfs(x+1,0,mask);
		else dfs(x,y+1,mask);
		return;
	}
	int id;
	
	if(y<7 && !ans[x][y+1]){
		
		id = ID(g[x][y],g[x][y+1]);
		if(~mask & (1 << id)){
			ans[x][y] = ans[x][y+1] = id;
			//fprintf(stderr,"%d %d = %d\n",x,y,id);
			//out(stderr,ans);
			if(y == 6) dfs(x+1,0,mask | (1 << id));
			else dfs(x,y+2,mask | (1<<id));
			ans[x][y] = ans[x][y+1] = 0;
		} 		
	}

	if(x<6 && !ans[x+1][y]){		
		id = ID(g[x][y],g[x+1][y]);
		if(~mask & (1 << id)){
			ans[x][y] = ans[x+1][y] = id;
			//fprintf(stderr,"%d %d | %d\n",x,y,id);
			//out(stderr,ans);
			if(y == 7) dfs(x+1,0,mask | (1 << id));
			else dfs(x,y+1,mask | (1<<id));
			ans[x][y] = ans[x+1][y] = 0;
		}	
	}
	
}

inline bool read(){
	int i,j;
	for(i=0;i<7;i++) for(j=0;j<8;j++) {
		if(scanf("%d",&g[i][j])==EOF) return false;		
	}
	return true;
}

void test_ID(){
	for(int i = 0; i< 7; i++) for(int j = i;j < 7 ;j++) fprintf(stderr,"%d %d : %d\n",i,j,ID(i,j));
}

int main(){
	int T = 0;
	//freopen("221.log","w",stderr);
	//test_ID();
	while(read()){
		if(T++) puts("\n\n");
		printf("Layout #%d:\n\n", T);
		out(stdout,g);
		printf("Maps resulting from layout #%d are:\n\n", T);
		cnt = 0;
		memset(ans,0,sizeof(ans));
		dfs(0,0,0);
		printf("There are %d solution(s) for layout #%d.\n",cnt,T);
	}
	return 0;
}
