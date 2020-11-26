#include <cstdio>
#include <set>
#include <list>
#include <algorithm>

struct Square{
	int x,y;
	Square(int _x,int _y):x(_x),y(_y){}
	Square():x(1),y(1){}	
	bool operator == (const Square &rhs) const{
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const Square &rhs) const{
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
};

struct Polyomino{
	int width,heigth;
	std::list<Square> squares;
	Polyomino():width(0),heigth(0){
		squares.clear();
	}
	inline void rotate(){
		int t;
		std::swap(width,heigth);
		for(auto &s : squares){
			t = s.x;
			s.x = s.y;
			s.y = width - t + 1;
		}
		squares.sort();
	}
	inline void flipY(){
		for(auto &s : squares){
			s.y = width - s.y + 1;
		}
		squares.sort();
	}

	inline void flipX(){
		for(auto &s : squares){
			s.x = heigth - s.x + 1;
		}
		squares.sort();
	}
	inline bool addSquare(int x,int y){
		Square t(x,y);
		if(std::find(squares.begin(),squares.end(),t) != squares.end()) return false;
		squares.push_back(t);
		if(x > heigth) heigth = x;
		if(y > width) width = y;
		if(x == 0) {
			heigth++;
			for(auto &s : squares) s.x++;
		}
		if(y == 0) {
			width++;
			for(auto &s : squares) s.y++;
		}
		squares.sort();
		return true;
	}
	bool operator == (const Polyomino &rhs) const{
		if( (width == rhs.width && heigth == rhs.heigth) ||
			(width == rhs.heigth && heigth == rhs.width) ){
			if(squares == rhs.squares) return true;
			Polyomino t = rhs;
			for(int i=0;i<3;i++) {
				t.rotate();
				if(squares == t.squares) return true;
			}

			t = rhs;
			t.flipY();
			if(squares == t.squares) return true;
			for(int i=0;i<3;i++) {
				t.rotate();
				if(squares == t.squares) return true;
			}

			t = rhs;
			t.flipX();
			if(squares == t.squares) return true;
			for(int i=0;i<3;i++) {
				t.rotate();
				if(squares == t.squares) return true;
			}
		}
		return false;
	}
};

std::list<Polyomino> ans[11];

void generate(int sz){
	const int dx[4] = {0,-1,0,1},dy[4]={-1,0,1,0};
	int i;
	for(auto prev : ans[sz - 1]){
		for(auto s : prev.squares){
			for(i=0;i<4;i++){
				Polyomino t = prev;
				if(t.addSquare(s.x+dx[i], s.y+dy[i])){
					for(auto curr : ans[sz]) if(t == curr) goto next;
					ans[sz].push_back(t);
				}	
			next: ;
			}
		}
	}
	//debug
	int k = 0;
	printf("%d : %llu\n",sz,ans[sz].size());
	// for(auto curr : ans[sz]){
	// 	printf("%d : %d %d :",++k,curr.width,curr.heigth);
	// 	for(auto s : curr.squares){
	// 		printf(" (%d,%d),",s.x,s.y);
	// 	}
	// 	printf("\n");
	// }
	
}

void init(){
	int i;
	Polyomino t;
	t.width = t.heigth = 1;
	t.squares.push_back(Square(1,1));
	ans[1].push_back(t);
	for(i=2;i<11;i++) generate(i);
}

int tab[10][10][10];

int main(){
	int n,w,h;

	init();
	for(n=1;n<=10;n++) {
		for(auto t : ans[n]){
			for(w=1;w<=10;w++) 
				for(h=1;h<=10;h++) 
					if(w >= t.width && h >= t.heigth || h >= t.width && w >= t.heigth) 
						tab[n-1][w-1][h-1]++;
		}
	}
	freopen("1602tab.txt","w",stdout);
	printf("a[10][10][10]={");
	for(n=0;n<10;n++) {
		for(w=0;w<10;w++) for(h=0;h<10;h++) printf("%d%c",tab[n][w][h],",}"[n*w*h==9*9*9]);
	}
	return 0;
}