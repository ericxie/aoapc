#include <cstdio>
#include <stack>
#include <utility>

int m[26][2];

int main(){
	int n,x,y;
	char c;
	scanf("%d ",&n);
	while(n--){
		scanf("%c %d %d ",&c,&x,&y);
		m[c-'A'][0] = x;
		m[c-'A'][1] = y;
	}

	char buf[111];
	
	while(gets(buf)){
		long long ans = 0;
		std::stack<std::pair<int,int> > s;
		char *p;
		for(p=buf;*p;p++) {
			if(*p==')'){
				auto m2 = s.top();
				s.pop();
				auto m1 = s.top();
				s.pop();
				if(m1.second != m2.first) goto error;
				ans += m1.first*m1.second*m2.second;
				s.emplace(m1.first,m2.second);
			} else if(*p>='A' && *p <= 'Z') s.emplace(m[*p-'A'][0],m[*p-'A'][1]);
		}
		printf("%lld\n",ans);
		continue;
		error: puts("error");
	}
	return 0;
}