#include <cstdio>
#include <cstring>
#include <stack>
#include <unordered_map>
#include <cassert>
typedef long long LL;

std::unordered_map<LL,int> a; 
int leaf;
int pos[2222222];
char s[2222222];

void init(){
	std::stack<int> sk;
	memset(pos,-1,sizeof(pos));
	for(char *p=s; *p; p++){
		if(*p == '[') sk.push(p-s);
		else if(*p==']') {
			pos[sk.top()] = p - s;
			sk.pop();
		}
	}
	//for(int i=0;s[i];i++) fprintf(stderr,"%d,",pos[i]);
	//fprintf(stderr,"\n");
}

void expr1(int L,int R,int depth);

void expr0(int L,int R,int depth){
	//assert(L<=R);
	if(s[L]=='[') expr1(L+1,pos[L]-1,depth+1);
	else{
		LL t;
		leaf++;
		sscanf(s+L,"%lld",&t);
		//fprintf(stderr,"%d:%lld\n",leaf,t);
		a[(1LL<<depth)*t]++;
	}
}

void expr1(int L,int R,int depth){
	//assert(L<=R);
	if(s[L]=='['){
		expr0(L,pos[L],depth);
		expr0(pos[L]+2,R,depth);
	} else {
		int i;
		for(i=L+1;s[i]!=',';i++);
		expr0(L,i-1,depth);
		expr0(i+1,R,depth);
	}	
}

int main(){
	int T;
	
	scanf("%d",&T);
	while(T--){
		fprintf(stderr,"%d\n",T);
		scanf("%s",s);
		leaf = 0;		
		init();
		a.clear();
		expr0(0,strlen(s)-1,0);
		int max = 0;
		for(auto &x : a){
			if(x.second > max) max = x.second; 
		}
		printf("%d\n",leaf-max);
	}
	return 0;
}