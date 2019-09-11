#include <cstdio>
#include <cstring>

char puzzle[12][12];
char buf[12][12];
int pos[12][12];

void getPos(int n,int m){
	int i,j,k=0;
	memset(pos,0,sizeof(pos));
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			if(puzzle[i][j] != '*' && (puzzle[i-1][j] == '*' || puzzle[i][j-1] == '*')) 
				pos[i][j] = ++k;
}

void out(int type,int n,int m){
	int i,j,x,y;
	const int delta[2][2]={{0,1},{1,0}};
	puts(type?"Down":"Across");
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(buf[i][j]!='*'){
				printf("%3d.",pos[i][j]);
				for(x=i,y=j;buf[x][y]!='*';x+=delta[type][0],y+=delta[type][1]){
					putchar(buf[x][y]);
					buf[x][y]='*';
				}
				putchar('\n');	
			}
		}
	}
}

int main(){
	int T=0,i,j,n,m;
	char s[11];
	while(gets(s),s[0]!='0'){
		sscanf(s,"%d %d",&n,&m);

		memset(puzzle,'*',sizeof(puzzle));
		for(i=1;i<=n;i++) {
			for(j=1;j<=m;j++) puzzle[i][j] = getchar();
			getchar();
		}
		getPos(n,m);

		if(T) putchar('\n');
		printf("puzzle #%d:\n",++T);
		for(i=0;i<2;i++){
			memcpy(buf,puzzle,sizeof(puzzle));
			out(i,n,m);	
		}
	}
	return 0;
}

/*
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0


*/