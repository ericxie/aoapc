#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <cctype>

struct array{
	int n;
	std::unordered_map<int,int> val;
	array():n(-1){}
	int get(int idx){
		if(n == -1 || idx < 0 || idx >= n) return -1;		
		auto it = val.find(idx); 
		if(it != val.end()){
			return it->second; 
		} else 
			return -1;
	}
	int set(int idx,int x){
		if(n == -1 || idx < 0 || idx >= n || x < 0) return -1;		
		val[idx] = x; 
		return 0;
	}
	void init(){
		n = -1;
		val.clear();
	}
};

array ar[52];

int number(char *s){
	int ret = 0;
	while(isdigit(*s)){
		ret *= 10;
		ret += *s - '0';
		s++;
	}
	return ret;
}

int name(char c){
	int idx = c - 'A';
	if(idx > 25) idx -= 'a'-'Z' - 1;
	return idx;
}

int declaration(char *s){
	int idx = name(*s);
	array *p = ar + idx;
	p->init();
	p->n = number(s+2);
	return 0;
}

int expr(char *s);

int arr_expr(char *s){
	int idx = name(*s);
	array *p = ar + idx;
	if(p->n == -1) return -1;
	else{
		return p->get(expr(s+2));
	}
}

int expr(char *s){
	if(isdigit(*s)) return number(s);
	else return arr_expr(s);
}

int assign(char *s){
	char *le,*re;	
	for(le=re=s;*re!='=';re++);
	*re++ = 0;
	int idx = name(*s);
	array *p = ar + idx;
	idx = expr(le+2);
	int val = expr(re);
	return p->set(idx,val);
}

void solve(){
	char buf[111];
	int ans = 0,line=0,ret;
	while(gets(buf)){
		line++;
		if(buf[0]=='.') {
			if(line == 1) return;
			printf("%d\n",ans);
			for(int i=0;i<52;i++) 	ar[i].init();
			ans = line = 0;
		} else {
			if(ans) continue;
			//printf("%d %s:",line,buf);
			if(strchr(buf,'=')){
				ret = assign(buf);
			} else {
				ret = declaration(buf);
			}
			//printf("%d\n",ret);
			if(ret == -1) ans = line;
		}
	}
}

int main(){
	solve();
}

