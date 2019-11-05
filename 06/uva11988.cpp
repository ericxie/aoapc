#include <cstdio>
#include <list>

int main(){
	char c;
	std::list<char> s;
	auto it = s.begin();
	while(c=getchar(),c!=EOF){
		if(c=='\n') {
			for(auto &ch : s) putchar(ch);
			putchar('\n');
			s.clear();
			it = s.begin();
		} else if(c=='['){
			it = s.begin();
		} else if(c==']'){
			it = s.end();
		} else it = s.insert(it,c), ++it;
	}
	return 0;
}