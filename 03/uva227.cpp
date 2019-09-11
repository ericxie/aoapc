#include <cstdio>
#include <algorithm>

char puzzle[7][7];

const int delta[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int move(int type,int &cx,int &cy){
	int x,y;
	x = cx + delta[type][0];
	y = cy + delta[type][1];
	if(!puzzle[x][y]) return 0;
	std::swap(puzzle[x][y],puzzle[cx][cy]);
	cx = x , cy = y;
	return 1;
}

void outPuzzle(){
	int i,j;
	for(i=1;i<6;i++)
		for(j=1;j<6;j++) 
			printf("%c%c",puzzle[i][j]," \n"[j==5]);
}


int main(){
	int i,j,T=0,x=0,y=0,n;
	char c,op[1111];
	for(;;){
		gets(&puzzle[1][1]);
		if(puzzle[1][1]=='Z') break;
		if(T) putchar('\n');
		printf("Puzzle #%d:\n",++T);
		
		for(i=2;i<6;i++) gets(&puzzle[i][1]);
		//puts("input:"),outPuzzle();
		for(i=1;i<6;i++) for(j=1;j<6;j++) if(puzzle[i][j]==' ') {
			x = i, y = j;
			goto readop;
		}
readop:
		for(n=0;(c=getchar())!='0';n++){
			switch(c){
				case 'A': op[n] = 0; break;
				case 'B': op[n] = 1; break;
				case 'L': op[n] = 2; break;
				case 'R': op[n] = 3; break;
				default: n--;
			}
		}
		getchar();
		//for(i=0;i<n;i++) printf("%d",op[i]);
		//putchar('\n');

		
		for(i=0;i<n;i++){
			//printf("%d %d\n",x,y);
			if(!move(op[i],x,y)){
				puts("This puzzle has no final configuration.");
				goto next;
			} 
		}
		outPuzzle();

next: ;
	}
	
	return 0;
}

/*
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAAAABBRRRLL0
Z


*/
