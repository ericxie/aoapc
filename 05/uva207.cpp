#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int TAG  = 1111;

struct player{
	char name[22];	// 姓名
	int holes[4];	// 四场成绩
	int num;		// 有效成绩数	
	int total2;		// 前两场成绩和
	int total;		// 总成绩
	int rank;		// 总成绩排名
	int rank2;		// 职业选手排名
	double prize;	// 分得奖金数
	bool star;		// 业余选手	
	bool tie;		// T标志
	void out(){
		int i;
		printf("%-21s",name);
		
		i = 0;
		if(num == 4){
			i = printf("%d",rank);
			if(tie) putchar('T'),i++;
		}		
		for(;i<10;i++) putchar(' ');
		
		for(i=0;i<4;i++){
			if(i<num) printf("%-5d",holes[i]);
			else printf("%5s"," ");
		}
		
		if(num == 4) {
			if(rank2 > 70) printf("%d\n",total);
			else printf("%-10d$%9.2f\n",total,prize);
		} else printf("DQ\n");
	}
};

std::vector<player> pga;

double amount,percent[222];

void readPrize(){
	scanf("%lf",&amount);
	for(int i=0;i<70;i++){
		scanf("%lf",percent+i);
	}
}

void readPlayers(){
	int n;
	char buf[111];
	scanf("%d ",&n);
	pga.clear();
	player t;
	for(int i=0;i<n;i++){
		gets(buf);
		strncpy(t.name,buf,20);
		t.name[20] = 0;
		t.star  = strchr(t.name,'*') != NULL; 
		if(t.star) t.rank2 = TAG;
		t.holes[0] = t.holes[1] = t.holes[2] = t.holes[3] = TAG;
		t.num = sscanf(buf+20,"%d %d %d %d",t.holes,t.holes+1,t.holes+2,t.holes+3);
		t.total2 = t.holes[0] + t.holes[1];
		t.total = t.holes[0] + t.holes[1] + t.holes[2] + t.holes[3];
		t.tie = false;
		t.prize = 0.0;
		pga.push_back(t);
	}
}

bool cmp1(const player &a,const player &b){
	return a.total2 < b.total2;
}

bool cmp2(const player &a,const player &b){
	if(a.total == b.total) return strcmp(a.name,b.name) < 0;
	else return a.total < b.total;
}

void advance(){
	int i,n;

	std::sort(pga.begin(),pga.end(),cmp1);
	n = pga.size();		
	for(i=70;i<n && pga[i].total2 == pga[i-1].total2; i++) ;
	if(i<n) pga.erase(pga.begin()+i,pga.begin()+n);
}

void process(){
	int i,j,k,n,c,p;
	double prize;
	std::sort(pga.begin(),pga.end(),cmp2);
	n = pga.size();
	p = 0;
	for(i=0; i<n; i=j){
		c = !pga[i].star;
		prize = 0.0;
		for(j=i+1; j<n && pga[i].total == pga[j].total; j++)  c += !pga[j].star;
		if(c){			
			for(k=0; k<c; k++) prize += percent[p+k];
			prize = amount * prize / 100.0 / c;			
		}
		for(k=i; k<j; k++){
			pga[k].rank = i+1;
			if(!pga[k].star) {
				pga[k].rank2 = p + 1;
				pga[k].tie = c > 1 && p<70;
				pga[k].prize = prize;
			}			
		} 
		p += c;
	}
}

void print(){
	int i;
	printf("%-21s%-10s%-5s%-5s%-5s%-5s%-10s%-s\n","Player Name","Place","RD1","RD2","RD3","RD4","TOTAL","Money Won");
	for(i=0;i<21+10+5*4+20;i++) putchar('-');
	putchar('\n');
	for(auto it=pga.begin(); it != pga.end(); ++it){
		it->out();
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		readPrize();
		readPlayers();
		advance();
		process();
		print();	
		if(T) putchar('\n');
	}
	
	return 0;
}

