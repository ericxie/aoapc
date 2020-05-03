#include <cstdio>
#include <list>
#include <stack>
#include <iterator>

std::list<std::stack<std::pair<char,char> > > cards;

inline bool match(const std::pair<char,char> &a,const std::pair<char,char> &b) {
	return a.first == b.first || a.second == b.second;
}

inline void move(std::list<std::stack<std::pair<char,char> > >::iterator des,std::list<std::stack<std::pair<char,char> > >::iterator src){
	auto t = src->top();
	src->pop();
	des->push(t);
	if(src->empty()) cards.erase(src);
}

inline void add(const char *s){
	std::stack<std::pair<char,char> > t ;
	t.push(std::make_pair(s[0],s[1]));
	cards.push_back(t);
}

void out(){
	for(auto it = std::next(cards.begin(),3); it != cards.end(); it++){
		printf(" %c%c(%lld)",it->top().first,it->top().second,it->size());
	}
	putchar('\n');
}

bool gao(){
	for(auto it = std::next(cards.begin(),3); it != cards.end(); it++){
		auto prev3 = std::prev(it,3) ; 
		auto prev1 = std::prev(it,1) ;							
		if(match(prev3->top(),it->top())){
			move(prev3,it);
			return true;
		} else if(match(prev1->top(),it->top())){
			move(prev1,it);
			return true;
		}
	}
	return false;
}

void solve(){
	while(gao());
	int n = cards.size() - 3;
	printf("%d %s remaining:",n,n==1?"pile":"piles");	
	for(auto it = std::next(cards.begin(),3) ; it != cards.end(); it++){
		printf(" %lld",it->size());
	}
	putchar('\n');
}

int main(){
	char s[4];
	for(;;){
		scanf("%s",s);
		if(s[0]=='#') break;
		cards.clear();
		for(int i=0;i<3;i++) add("**");
		add(s);
		for(int i = 1; i < 52; i++){
			scanf("%s",s);
			add(s);
		}		
		solve();
	}
	return 0;
}
