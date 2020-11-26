#include <cstdio>
#include <cstring>

int dir[8][7] = {
	{0,2,6,11,15,20,22},
	{1,3,8,12,17,21,23},
	{10,9,8,7,6,5,4},
	{19,18,17,16,15,14,13}
}; 

const int rev[8] = {5,4,7,6,1,0,3,2}; 

int puzzle[24];
char move[1111];

inline void shift(int k){
	int t;
	t = puzzle[dir[k][0]];
	for(int i=0;i<6;i++) puzzle[dir[k][i]] = puzzle[dir[k][i+1]];
	puzzle[dir[k][6]] = t;
}

inline int hx(){
	int i,k,pos[8] = {6,7,8,11,12,15,16,17},h=0,t;
	for(k=1;k<=3 && h < 8;k++) {
		for(t=i=0;i<8;i++) t += puzzle[pos[i]] == k;
		if(t > h) h = t;
	}
	return h;
}

void out(){
	int i,j,k=0;
	for(j=0;j<7;j++){
		if(j==2 || j==4){
			for(i=0;i<7;i++) fprintf(stderr,"%d",puzzle[k++]);
			fprintf(stderr,"\n");
		} else {
			fprintf(stderr," ");
			for(i=0;i<2;i++) fprintf(stderr," %d",puzzle[k++]);
			fprintf(stderr,"\n");
		}
	}	
}

int dfs(int maxd,int d,int h){
	if(d == maxd){
		if(h == 8)  {
			if(d){
				move[d] = 0;
				puts(move);
			} else {
				puts("No moves needed");
			}
			printf("%d\n",puzzle[6]);
			return 1;
		}
		return 0;
	}
	if(d + 8 - h > maxd) return 0;
	//fprintf(stderr,"%d %d : %d , ",maxd,d,h);
	//for(int i=0;i<d;i++) fprintf(stderr,"%c",move[i]);
	//fprintf(stderr,"\n");
	//out();
	for(int i=0;i<8;i++){
		shift(i);
		move[d] = 'A' + i;
		if(dfs(maxd,d+1,hx())) return 1;
		shift(rev[i]);
	}
	return 0;
}

int ida(int h){
	int depth;
	for(depth=0;;depth++){
		if(dfs(depth,0,h)) return 1;
	}
	return 0;
}

int main(){
	int i,j;
	for(i=4;i<8;i++) for(j=0;j<7;j++) dir[i][j] = dir[rev[i]][6-j];
	while(scanf("%d",puzzle),puzzle[0]){
		for(i=1;i<24;i++) scanf("%d",puzzle+i);
		//out();		
		ida(hx());
	}
	return 0;
}
