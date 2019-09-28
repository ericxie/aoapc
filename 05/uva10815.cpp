#include <cstdio>
#include <cctype>
const int maxn = 200000;

struct trie{
	struct node{
		int c;
		int next[26];
	};
	
	node *kt;
	int last;
	char buf[1111];
	int k;
	
	trie():last(1){ kt = new node[maxn];};
	~trie(){delete[]kt;}

	void insert(int id,char *s){
		if(*s == 0) kt[id].c++;
		else {
			if(kt[id].next[*s-'a'] == 0) kt[id].next[*s-'a'] = ++last;
			insert(kt[id].next[*s-'a'],s+1);
		}
	}

	void _out(int id){
		if(kt[id].c){
			for(int i=0;i<k;i++) putchar(buf[i]);
			putchar('\n');
		}
		for(int i=0;i<26;i++) if(kt[id].next[i]){
			buf[k++] = 'a' + i;
			_out(kt[id].next[i]);
			k--;
		}
	}

	void out(){
		k = 0;
		_out(1);
	}
};

char str[1000111];

int main(){
	char *p,*q;
	trie a;
	size_t c;
	c = fread(str,1,1000000,stdin);
	str[c] = str[c+1] = 0;
	p = str;
	
	while(*p){
		while(*p && !isalpha(*p)) p++;
		for(q=p;isalpha(*q);q++) *q = tolower(*q);
		*q = 0;
		if(*p) a.insert(1,p);
		p = q + 1;
	}
	a.out();
	return 0;
}