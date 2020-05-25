#include <cstdio>
#include <cstring>
#include <list>
#include <tuple>

struct cell{
	int value;
	std::list<std::tuple<int,int,int> > depends;
	char s[111];
	bool tag;
	int vis;
	cell(){
		value = 0;
		depends.clear();
		*s = 0;
		tag =false; 
		vis = 0;
	}	
	void out(){
		fprintf(stderr,"%d %d %d %s :",value,tag,vis,s);
		for(auto & a : depends){
			fprintf(stderr,"(%d %c%d),",std::get<0>(a),std::get<1>(a)+'A',std::get<2>(a));
		}
		fprintf(stderr,"\n");
	}
}sheet[33][33];

bool cycle;

void parse(cell &a,char *s){
	int t;
	char ch;
	strcpy(a.s,s);
	int sign = 1;
	if(*s == '-') sign = -1 , s++;

	while(*s){
		if(isdigit(*s)) {
			sscanf(s,"%d",&t);
			a.value  += sign * t;	
		} else {
			a.tag = true;
			sscanf(s,"%c%d",&ch,&t);
			a.depends.push_back(std::make_tuple(sign,ch-'A',t));
		}	
		while(*s!='+'&&*s!='-'&&*s) s++;
		if(*s == '-') sign = -1 , s++;
		else if(*s == '+') sign = 1, s++; 
	}
}

bool dfs(cell &u){

	u.vis = 1;
	for(auto &a : u.depends){
		int sign = std::get<0>(a);
		int x = std::get<1>(a);
		int y = std::get<2>(a);
		cell &v = sheet[x][y];
		if(v.vis == 0) {
			//fprintf(stderr,"%d %d : %s\n",x,y,u.s);
			if(!dfs(v)) return false;
		} else if(v.vis == 1) {
			cycle = true;
			return false;
		}
		u.value += sign * v.value;
	}
	u.tag = false;
	u.vis = 2;
	return true;
}

void out_fail(int n,int m){
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<m;j++) {
		auto &a = sheet[i][j];
		if(a.tag){
			printf("%c%d: %s\n",i + 'A', j, a.s);
		}
	}
}

void out_success(int n,int m){
	int i,j;
	putchar(' ');
	for(j=0;j<m;j++) printf("%6d",j);
	putchar('\n');
	for(i=0;i<n;i++) {
		putchar('A'+i);
		for(j=0;j<m;j++) printf("%6d",sheet[i][j].value);
		putchar('\n');
	}
}

void solve(int n,int m){
	int i,j;
	cycle = false;
	for(i=0;i<n;i++) for(j=0;j<m;j++) if(sheet[i][j].vis == 0) dfs(sheet[i][j]);
	if(cycle) out_fail(n,m);
	else out_success(n,m);
	putchar('\n');
}

int main(){
	int n,m,i,j;
	char s[111];
	while(scanf("%d %d",&n,&m),n!=0&&m!=0){
		for(i=0;i<n;i++) for(j=0;j<m;j++){
			sheet[i][j] = cell();
			scanf("%s",s);
			parse(sheet[i][j],s);	
			//fprintf(stderr,"%d %d - ",i,j);
			//sheet[i][j].out();
		}
		//fprintf(stderr,"%d %d\n",n,m);
		solve(n,m);

	}
	return 0;
}
