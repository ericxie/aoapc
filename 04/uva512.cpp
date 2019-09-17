#include <cstdio>

int ops[11111][55];

void solve(int x, int y, int n){
	int i,j,m,cx=x,cy=y;
	for(i=0;i<n;i++){
		m = ops[i][1];
		switch(ops[i][0]){
			case 0:
				for(j=0;j<m;j++){
					if(ops[i][2+j]<cy) y--;
					else if(ops[i][2+j] == cy){
						puts("GONE");
						return;
					} 
				}
				break;
			case 1:
				for(j=0;j<m;j++){
					if(ops[i][2+j]<cx) x--;
					else if(ops[i][2+j] == cx){
						puts("GONE");
						return;
					} 
				}
				break;
			case 2:
				for(j=0;j<m;j++){
					if(ops[i][2+j]<=cy) y++; 
				}
				break;
			case 3:
				for(j=0;j<m;j++){
					if(ops[i][2+j]<=cx) x++; 
				}
				break;
			case 4:
				if(ops[i][2] == cx && ops[i][3] == cy)
					x = ops[i][4], y = ops[i][5];
				else if(ops[i][4] == cx && ops[i][5] == cy)
					x = ops[i][2], y = ops[i][3];
				break;
		}
		cx = x , cy = y;
	}
	printf("moved to (%d,%d)\n",cx,cy);
}


int main(){
	int n,m,i,j,R,C,x,y,T=0;
	char buf[111];
	while(scanf("%d %d",&R,&C),R!=0){
		if(T) putchar('\n');
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%s",buf);
			switch(buf[0]+buf[1]){
				case 'D'+'C': ops[i][0] = 0; break;
				case 'D'+'R': ops[i][0] = 1; break;
				case 'I'+'C': ops[i][0] = 2; break;
				case 'I'+'R': ops[i][0] = 3; break;
				case 'E'+'X': ops[i][0] = 4; break;
			}
			if(ops[i][0]!=4) scanf("%d",&ops[i][1]);
			else ops[i][1] = 4;
			for(j=0;j<ops[i][1];j++) scanf("%d",&ops[i][2+j]);
		}
		printf("Spreadsheet #%d\n",++T);
		scanf("%d",&m);
		for(i=0;i<m;i++){
			scanf("%d %d",&x,&y);
			printf("Cell data in (%d,%d) ",x,y);
			solve(x,y,n);
		}

	}
	return 0;
}