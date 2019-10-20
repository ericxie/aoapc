#include <string>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>

struct book{	
	std::string title;
	std::string author;
	int status; 	// 0 no move, 1 moved, 2 borrowed.
	book(std::string title,std::string author):title(title),author(author),status(0){};
	bool operator<(const book &rhs) const{
		if(author == rhs.author) return title < rhs.title;
		return author < rhs.author;
	}
};

std::vector<book> shelve;

void readBook(){
	std::string buf;
	std::regex book_reg("^(\".*\") by (.*)$");
    shelve.clear();
    while(std::getline(std::cin,buf)){
    	//std::cerr << buf << "\n";
        if(buf[0]=='E') return;
        std::smatch res;
        if(std::regex_search(buf,res,book_reg)){
        	//std::cerr << res[1] << ',' << res[2] << '\n';
         	shelve.emplace_back(res[1],res[2]);
        }
    }
}

void solve(){
	std::string buf;
	std::sort(shelve.begin(),shelve.end());
	while(std::getline(std::cin,buf)){
		if(buf[0] == 'E') break;
		else if(buf[0] == 'B'){
			buf = buf.substr(7,buf.size()-7);
			//std::cerr << "***" << buf << "\n";
			for(auto &x : shelve) if(x.title == buf){
				x.status = 2;
				break;
			}
			
		} else if(buf[0] == 'R'){
			buf = buf.substr(7,buf.size()-7);
			//std::cerr << "+++" << buf << "\n";
			for(auto &x : shelve) if(x.title == buf){
				x.status = 1;
				break;
			}
		} else {
			for(auto it = shelve.begin(); it != shelve.end(); ++it){
				if(it->status == 1) {
					if(it == shelve.begin()){
						std::cout << "Put " << it->title << " first\n"; 						
					} else {
						auto it1 = it - 1;
						while(it1 != shelve.begin() && it1->status != 0) --it1;
						if(it1->status == 0)
							std::cout << "Put " << it->title << " after " << it1->title << "\n";
						else 
							std::cout << "Put " << it->title << " first\n";
					}
					it->status = 0;
				}
			}
			std::cout << "END\n";
		}
		//std::cerr << "---" << buf << "\n";
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	readBook();
	solve();
	return 0;
}

