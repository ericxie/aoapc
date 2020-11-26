#include <cstdio>
#define DEBUG 0

int X[5][6][5];
int Y[5][5][6];

void XY(){
	int i,j,k,no;
	for(i=0;i<5;i++){
		no = 1;
		for(j=0;j<=i;j++){
			for(k=0;k<=i;k++)   X[i][j][k] = no++;
			for(k=0;k<=i+1;k++) Y[i][j][k] = no++;
		} 		
		for(k=0;k<=i;k++) X[i][j][k] = no++; 
	}
}

bool isGrid(int n,int x,int y,int w,long long mask){
	int i;
	for(i=0;i<w;i++) {		
		//fprintf(stderr," X: %d %d\n",X[n-1][x][y+i],X[n-1][x+w][y+i]);
		if(mask & (1LL << X[n-1][x][y+i])) return false;
		if(mask & (1LL << X[n-1][x+w][y+i])) return false;
	}
	for(i=0;i<w;i++){
		//fprintf(stderr," Y: %d %d\n",Y[n-1][x+i][y],Y[n-1][x+i][y+w]);
		if(mask & (1LL << Y[n-1][x+i][y])) return false;
		if(mask & (1LL << Y[n-1][x+i][y+w])) return false;
	}
	return true;
}

int hx(int sz,long long mask){
	int x,y,w,h=0;
	//fprintf(stderr,"= %d %llx =\n",sz,mask);
	for(w=1;w<=sz;w++){
		for(x=0;x<sz-w+1;x++)
			for(y=0;y<sz-w+1;y++){
				h +=isGrid(sz,x,y,w,mask);
				//fprintf(stderr,"%d %d %d : %d\n",w,x,y,h);
			}
	}
	
	return h;
}

void outXY(int n){
	int i,j;
	for(i=0;i<n;i++) {
		fprintf(stderr,"  ");
		for(j=0;j<n;j++) fprintf(stderr,"--%2d--",X[n-1][i][j]);
		fprintf(stderr,"\n");
		for(j=0;j<=n;j++) fprintf(stderr,"%2d    ",Y[n-1][i][j]);
		fprintf(stderr,"\n");		
	}
	fprintf(stderr,"\n");
	for(j=0;j<n;j++) fprintf(stderr,"--%2d--",X[n-1][i][j]);
	fprintf(stderr,"\n");
}

bool dfs(int maxd,int d,int h,int k,int sz,long long mask){
	//fprintf(stderr,"%d %d : %d %d %llx\n",maxd,d,h,sz,mask);
	if(d == maxd) return h == 0;
	if(h > sz*(maxd-d)) return false;   // 不是太严谨，但是问题不大
	int n = 2 * sz * (sz+1);
	for(int i=k;i<=n;i++) {
		if(~mask & (1 << i)){
			long long t = mask | (1LL<<i);
			int nh = hx(sz,t);
			if(nh == h) continue;
			if(dfs(maxd,d+1,nh,i+1,sz,t)) return true; 
		}
	}
	return false;
}

int ida(int sz,long long mask){
	int i;
	for(i=0;;i++){
		if(dfs(i,0,hx(sz,mask),1,sz,mask)) return i;
	}
	return -1;
}

int main(){
	XY();
	
	int T,sz,i,n,t;
	long long mask;
	
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&sz,&n);
		//outXY(sz);
		mask = 0LL;
		for(i=0;i<n;i++) {
			scanf("%d",&t);
			mask |= 1LL << t;			
		}
		printf("%d\n",ida(sz,mask));
	}
	return 0;
}