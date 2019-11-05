#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
typedef unsigned int uint;

namespace bigint{
	const uint base = 1000000000;
	const uint size = 2400;
	const uint len = 9;
	struct U{
		uint a[size];
		uint length;
		U():length(0){memset(a,0,sizeof(a));}
		U(uint x){
			memset(a,0,sizeof(a));
			if(x < base) {
				a[0] = x;
				length = 1;
			} else {
				a[0] = x % base;
				a[1] = x / base;
				length = 2;
			}
		}
		U operator=(const U &rhs){
			memcpy(a,rhs.a,sizeof(a));
			length = rhs.length;
			return *this;
		}
		U operator+=(const U &rhs){
			uint i,c=0;
			if(length < rhs.length) length = rhs.length;
			for(i=0;i<length;i++){
				a[i] += rhs.a[i] + c;
				if(a[i]>=base){
					c = a[i] / base;
					a[i] %= base;
				} else c = 0;

			}
			if(c) a[length++] = c;
			return *this;
		}
		char * toString(char * buf){
			uint i,k;
			if(length == 1 && a[0] == 0) {
				buf[0]='0';
				buf[1]=0;
			} else {
				k = sprintf(buf,"%u",a[length - 1]);
				for(i = 0; i<length - 1 && k<=40; i++,k+=len){
					sprintf(buf+k,"%09u",a[length - i - 2]);
				}
				if(k>=40) k = 40;
				buf[k] = 0;
			}
			return buf;
		}
	};
};

namespace trie{
	const uint size = 4000000;
	uint last = 0;
	struct node{
		int n;
		node *next[10];
		node():n(-1){ memset(next,0,sizeof(next));}
	}kt[size];
	void insert(int k,const char *s){
		int n = strlen(s),t;
		node *p = kt;
		for(int i=0; i<n; i++){
			t = s[i] - '0';
			if(p->next[t] == NULL){
				kt[++last].n = k;
				p->next[t] = kt + last;
			}
			p = p->next[t];
		}
		if(p->n == -1) p->n = k;
	}
	int find(const char *s){
		int n = strlen(s),t;
		node *p = kt;
		for(int i=0;i<n;i++){
			t = s[i]-'0';
			if(p->next[t] == NULL) return -1;
			p = p->next[t];
		}
		return p->n;
	}
};

int main(){
	bigint::U a(1u),b(1u),c(0u);
	trie::insert(0,"1");
	char buf[55];
	for(int i=2;i<100000;i++){
		c = a;
		a += b;
		b = c;
		trie::insert(i,a.toString(buf));
    }
    //fprintf(stderr,"%u\n",trie::last);
	int T,k=0;
	scanf("%d ",&T);
	while(T--){
		gets(buf);
		printf("Case #%d: %d\n",++k,trie::find(buf));
	}
	return 0;
}

