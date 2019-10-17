#include <cstdio>

const int maxn = 120000*10;

struct node{
	int tag;
	int next[26];
}kt[maxn];
int cnt = 1;

void insert(char *s){
	node *p = kt;
	while(*s) {
		int i = *s - 'a';
		if(p->next[i]==0) p->next[i] = cnt++; 
		p = kt + p->next[i];
		s++;  
	}
	p->tag = true;
}

int _query(char *s){
	node *p = kt;
	while(*s){
		int i = *s - 'a';
		if(p->next[i] == 0) return 0;
		p = kt + p->next[i];
		s++; 
	} 
	return p->tag;
}

int query(char *s){
	node *p = kt;
	while(*s){
		if(p->tag) if(_query(s)) return 1;
		int i = *s - 'a';
		p = kt + p->next[i]; 
		s++;
	}
	return 0;
}

char dict[120000][111];

int main(){
	int i,n=0;
	while(gets(dict[n])){
		insert(dict[n++]);
	}
	for(i=0;i<n;i++) if(query(dict[i])) puts(dict[i]);
	return 0;
}