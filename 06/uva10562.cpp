#include <cstdio>
#include <cstring>

char a[222][222];

void prt_tree(int x,int y){
	putchar(a[x][y]);
	if(a[x+1][y] != '|') printf("()");
	else{
		x += 2;
		int left,right;
		for(left = y; left>=1 && a[x][left-1] == '-'; left--);
		for(right = y; right < 200 && a[x][right+1] == '-'; right++);
		x++;
		putchar('(');
		for(y=left;y<=right && a[x][y];y++) if(a[x][y]!=' '){
			prt_tree(x,y);
		}
		putchar(')');
	}
}

void solve(){
	int y=0;
	char *p;

	for(p=a[0];*p && *p==' '; p++,y++);
	putchar('(');
	if(*p && a[0][0] != '#') prt_tree(0,y);
	puts(")");
}

void read(){
	int x = 0;
	memset(a,' ',sizeof(a));
	while(gets(a[x]),a[x][0]!='#') x++;
}

int main(){
	int T;
	scanf("%d",&T);
	getchar();
	while(T--){
		read();
		solve();
	}
	return 0;
}

