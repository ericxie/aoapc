#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <cctype>

#define OUT_SEP std::cout << "----------\n"
#define OUT_END std::cout << "==========\n"
#define OUT_NON std::cout << "Sorry, I found nothing.\n"

struct Text{
	std::vector<std::string> lines;
	std::set<std::string> words;
	std::vector<std::set<std::string> > line_words;
	int n;

	void parse(std::string &s){
		std::regex word_reg("([A-Za-z]+)");
		std::smatch sm;
		std::set<std::string > t;
		while(std::regex_search(s,sm,word_reg)){
			auto word = sm.str();
			std::transform(word.begin(),word.end(),word.begin(),::tolower);
			std::cerr << word << '\n';
			if(word != "the" && word !="a" && word !="to" && 
			   word != "and" && word != "or" && word != "not") {
				words.insert(word);
				t.insert(word);
			}			
			s = sm.suffix();
		}
		line_words.push_back(t);
	}
	void read(){
		std::string buf;
		n = 0;
		while(std::getline(std::cin,buf),buf!="**********"){
			n++;
			std::cerr << n << ":" << buf << '\n';
			lines.push_back(buf);
			parse(buf);
		}
	}
	inline bool in_text(const std::string &word) const{
		auto it = words.find(word);
		return it != words.end(); 
	}
	inline bool in_line(int line ,const std::string &word) const{
		auto it = line_words[line].find(word);
		return it != line_words[line].end();
	}
	
};

namespace Problem{
	int n;
	bool flag;
	std::vector<Text> texts;
	void read(){
		int n;
		std::string buf;
		Text t;

		std::cin >> n;
		std::getline(std::cin,buf);
		texts.reserve(n);
		for(int i = 0; i < n; i++)	texts[i].read();
	}

	void AND(const std::string &word1,const std::string &word2){
		bool flag = false;
		for(int i=0; i < n; i++) {
			if(flag) flag = false, OUT_SEP;
			auto it = texts.begin() + i;
			if(it->in_text(word1) && it->in_text(word2)){
				for(int j = 0;j < it->n ; j++) 
					if(it->in_line(j,word1) || it->in_line(j,word2)) 
						std::cout << it->lines[j] << '\n';
				flag = true;
			}
		}
		if(!flag) OUT_NON;		
	}

	void OR(const std::string &word1,const std::string &word2){
		bool flag = false;
		for(int i=0; i < n; i++) {
			if(flag) flag = false, OUT_SEP;
			auto it = texts.begin() + i;
			if(it->in_text(word1) || it->in_text(word2)){
				for(int j = 0;j < it->n ; j++) 
					if(it->in_line(j,word1) || it->in_line(j,word2)) 
						std::cout << it->lines[j] << '\n';
				flag = true;
			}
		}
		if(!flag) OUT_NON;		
	}

	void IN(const std::string &word){
		bool flag = false;
		for(int i=0; i < n; i++) {
			if(flag) flag = false, OUT_SEP;
			auto it = texts.begin() + i;
			if(it->in_text(word)){
				for(int j = 0;j < it->n ; j++) 
					if(it->in_line(j,word)) 
						std::cout << it->lines[j] << '\n';
				flag = true;
			}
		}
		if(!flag) OUT_NON;		
	}

	void NOT(const std::string &word){
		bool flag = false;
		for(int i=0; i < n; i++) {
			if(flag) flag = false, OUT_SEP;
			auto it = texts.begin() + i;
			if(!it->in_text(word)){
				for(int j = 0;j < it->n ; j++) 
					std::cout << it->lines[j] << '\n';
				flag = true;
			}
		}
		if(!flag) OUT_NON;		
	}
	void query(){
		int m;
		std::string buf;
		std::cin >> m;
		std::getline(std::cin,buf);
		
		std::regex reg_and("^([a-z]+) AND ([a-z]+)$");
		std::regex reg_or("^([a-z]+) OR ([a-z]+)$");
		std::regex reg_not("^NOT ([a-z]+)$");
		std::regex reg_in("^([a-z]+)$");
		std::smatch sm;

		while(m--){
			std::getline(std::cin,buf);
			if(std::regex_match(buf,sm,reg_and)){
				AND(sm[1].str(),sm[2].str()); 
			} else if(std::regex_match(buf,sm,reg_or)){
				OR(sm[1].str(),sm[2].str()); 
			} else if(std::regex_match(buf,sm,reg_not)){
				NOT(sm[1].str()); 
			} else if(std::regex_match(buf,sm,reg_in)){
				IN(sm[1].str());
			} else {
				std::cerr << n << " Error\n";
			}
			OUT_END;
		}
	}
};

int main(){	
	Problem::read();
	//Problem::query();
}

