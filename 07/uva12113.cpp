#include <cstdio>
#include <unordered_set>
#include <algorithm>

std::unordered_set<long long> puzzle;

/*
+-00-+-01-+-02-+-03-+
04   05   06   07   08
+-09-+-10-+-11-+-12-+
13   14   15   16   17
+-18-+-19-+-20-+-21-+
22   23   24   25   26
+-27-+-28-+-29-+-30-+
31   32   33   34   35
+-36-+-37-+-38-+-39-+

0,1,4,6,13,15,18,19;
5,9,10,14;
*/

const long long set1 = (1<<0) | (1<< 1)  | (1<< 4) | (1<< 6) | (1<< 13) | (1<< 15) | (1<< 18) | (1<< 19);
const long long set0 = (1<<5) | (1<< 9)  | (1<< 10) | (1<< 14);

inline int get(int x,int y){ return x * 9 + y;}

inline long long add(long long s,int x,int y){
	int offset = get(x,y);
	s |= set1 << offset;
	s &= ~(set0 << offset);
	return s;
}

void dfs(long long s,int mask,int n){	
	if(n==7) return;
	if(s) puzzle.insert(s);
	int i,j,k;	
	for(i = k = 0;i < 3;i++) for(j=0;j<3;j++,k++) if(~mask & (1 << k)){
		dfs(add(s,i,j),mask|(1<<k),n+1);
	}
}

long long read(){
	long long r = 0;
	int i,j,k;
	char s[12];
	gets(s);
	
	if(s[0]=='0') return -1LL;
	for(i=1,k=0;i<9;i+=2,k++) if(s[i] == '_') r |= 1LL << k;
	for(i=0;i<4;i++){
		gets(s);		
		for(j=0;j<9;j+=2,k++) if(s[j] == '|') r |= 1LL << k;
		for(j=1;j<9;j+=2,k++) if(s[j] == '_') r |= 1LL << k;
	}	
	return r;
}

int main(){	
	dfs(0,0,0);	
	int k=0;
	long long r;
	while(r = read(),r!=-1LL){
		printf("Case %d: %s\n",++k,puzzle.find(r)==puzzle.end()?"No":"Yes");
	}
	return 0;
}

