#include <cstdio>
#include <list>
#include <set>
#include <typeinfo>
#include <iterator>
#include <array>

std::list<std::list<int> >piles;
std::set<std::list<std::list<int> > > us;

inline bool check(int *a){
	int s =a[0] + a[1] + a[2];
	//fprintf(stderr,"%d %d %d : %d\n",a[0],a[1],a[2],s);
	return s==10 || s==20 || s==30;
}

inline void push(int *a){
	auto it = piles.end();
	--it;
	for(int i = 0;i<3;i++) it->push_back(a[i]);
}

inline bool move(std::list<std::list<int>>::iterator x,int k){
	int pos[3][3]={{0,1,-1},{0,-2,-1},{-3,-2,-1}};
	int a[3];
	for(int i=0;i<3;i++) {
		if(pos[k][i]<0){
			auto it = x->end();
			a[i] = * std::prev(it,-pos[k][i]);
		} else {
			auto it = x->begin();
			a[i] = * std::next(it,pos[k][i]);
		}
	}
	if(check(a)){
		push(a);
		for(int i = 0;i < 3; i++) if(pos[k][i] < 0) x->pop_back();
		else x->pop_front();
		return true;
	}
	return false;
}

void out(std::list<std::list<int>>::iterator x){
	for(auto ix : *x) fprintf(stderr," %d",ix);
	fprintf(stderr,"\n");
}

void out_all(){
	int k = 0;
	for(auto it = piles.begin(); it!=piles.end(); ++it){
		fprintf(stderr,"%d:",++k) , out(it);
	}
	fprintf(stderr,"----------------------\n");
}

void process(std::list<std::list<int>>::iterator x){
	bool tag = true;
	while(tag && x->size() >= 3) {	
		tag = false;
		for(int i=0;i<3;i++){
			if(move(x,i)){
				tag = true;
				break;
			}
		}
	}	
}

void solve(){
	char s[][5]={"Win ","Loss","Draw"};
	int cnt = 0;
	int ans = 0;	
	us.clear();
	for(;;){
		auto last = piles.end();
		--last;			
		for(auto it = piles.begin(); it != last; ){
			if(last->empty()) {
				ans = 1;
				goto end;
			}
			int x = last->front();
			last->pop_front();
			it->push_back(x);
			cnt++;						
			process(it);
			if(it->size()==0) {
				it = piles.erase(it);
				last = piles.end();
				--last;
			} else ++it;			
			//out_all();
			if(piles.size() == 1) {
				ans = 0;
				goto end;
			}
			if(us.find(piles) != us.end()) {
				ans = 2;
				goto end;
			}
			us.insert(piles);			
		}
	}
end: 		printf("%s: %d\n",s[ans],cnt);
}

int main(){
	int i,t;
	for(;;){
		scanf("%d",&t);
		if(t==0) break;
		piles.clear();
		for(i=0;i<8;i++) piles.push_back(std::list<int>());
		auto it = piles.end(); 
		--it;
		it->push_back(t);
		for(i=1;i<52;i++){
			scanf("%d",&t);
			it->push_back(t);
		}
		solve();
	}
	return 0;
}