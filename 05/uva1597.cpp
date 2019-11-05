#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>


const size_t N = 100;

std::map<std::string,std::set<size_t> > indexDoc;
std::map<std::string,std::set<size_t> > indexContext[N];
std::vector<std::string> context[N];

size_t docNum;

void updateIndex(std::map<std::string,std::set<size_t> > &index, const std::string &key, const size_t val){
	auto it = index.find(key);
	if(it != index.end()){
		it->second.insert(val);
	} else {
		std::set<size_t> t;
		t.insert(val);
		index.emplace(key,t);
	}
}

void parse(std::string &s,size_t id,size_t line){
	std::regex word_reg("([A-Za-z]+)");
	std::smatch sm;
	while(std::regex_search(s,sm,word_reg)){
		auto word = sm.str();
		std::transform(word.begin(),word.end(),word.begin(),::tolower);
		
		if(word != "the" && word !="a" && word !="to" && 
		   word != "and" && word != "or" && word != "not") {
			//std::cerr << word << '\n';
			updateIndex(indexDoc,word,id);
			updateIndex(indexContext[id],word,line);
		}
		
		s = sm.suffix();
	}
}

void readText(){
	size_t i,line;
	std::cin >> docNum;
	std::string buf;
	std::getline(std::cin,buf);
	for(i=0;i<docNum;i++){
		line = 0;
		while(std::getline(std::cin,buf),buf!="**********"){			
			context[i].push_back(buf);
			parse(buf,i,line);	
			line++;		
		}
	}
}

inline void outLine(const size_t id,const std::vector<size_t> &lines, bool &tag){
	if(!tag) std::cout << "----------\n"; 
	for(auto line : lines) std::cout << context[id][line] << '\n';
	tag = false;
}

inline void outText(const size_t id, bool &tag){
	if(!tag) std::cout << "----------\n"; 
	for(auto x : context[id]) std::cout << x << '\n';
	tag = false;	
}

void AND(const std::string &word1,const std::string &word2){
	auto it1 = indexDoc.find(word1);
	if(it1 == indexDoc.end()) return;
	auto it2 = indexDoc.find(word2);
	if(it1 == indexDoc.end()) return;
	std::vector<size_t> res;
	std::set_intersection(it1->second.begin(),it1->second.end(),it2->second.begin(),it2->second.end(),std::back_inserter(res));
	if(res.size() == 0){
		std::cout << "Sorry, I found nothing.\n";
	} else {
		bool tag = true;
		for(size_t id : res){
			auto it1 = indexContext[id].find(word1);
			auto it2 = indexContext[id].find(word2);
			std::vector<size_t> lines;
			std::set_union(it1->second.begin(),it1->second.end(),it2->second.begin(),it2->second.end(),std::back_inserter(lines));
			outLine(id,lines,tag);
		}
	}
}

void OR(const std::string &word1,const std::string &word2){
	auto it1 = indexDoc.find(word1);
	auto it2 = indexDoc.find(word2);
	std::vector<size_t> res;
	if(it1 == indexDoc.end()){
		if(it2 == indexDoc.end()) {
			std::cout << "Sorry, I found nothing.\n";
			return;
		} else {
			for(size_t id : it2->second ) res.push_back(id); 
		}
	} else {
		if(it2 == indexDoc.end()){
			for(size_t id : it1->second ) res.push_back(id);	
		} else {		
			std::set_union(it1->second.begin(),it1->second.end(),it2->second.begin(),it2->second.end(),std::back_inserter(res));	
		}
	}
	
	bool tag = true;
	for(size_t id : res){
		auto it1 = indexContext[id].find(word1);
		auto it2 = indexContext[id].find(word2);
		std::vector<size_t> lines;
		if(it1 == indexContext[id].end()){
			for(size_t line : it2->second) lines.push_back(line);
		} else if (it2 == indexContext[id].end()){
			for(size_t line : it1->second) lines.push_back(line);
		} else 
			std::set_union(it1->second.begin(),it1->second.end(),it2->second.begin(),it2->second.end(),std::back_inserter(lines));
		outLine(id,lines,tag);
	}
	
}

void NOT(const std::string &word){
	auto it =  indexDoc.find(word);
	bool tag = true;
	if(it == indexDoc.end()){
		for(size_t i = 0;i < docNum; i++) outText(i,tag);
	} else {
		auto ids = it->second;
		bool flag = true;		
		for(size_t i = 0;i < docNum; i++) {
			if(ids.find(i) == ids.end()){
				flag = false;
				outText(i,tag);
			} 
		}
		if(flag) std::cout << "Sorry, I found nothing.\n";
	}
}

void IN(const std::string &word){
	auto it =  indexDoc.find(word);
	if(it == indexDoc.end()){
		std::cout << "Sorry, I found nothing.\n";
	} else {
		bool tag = true;
		for(size_t id : it->second){
			auto it2 = indexContext[id].find(word);
			if(!tag) std::cout << "----------\n";
			for(size_t line : it2->second) {
				std::cout << context[id][line] << '\n';
			}
			tag = false;
		}
	}
}

void query(){
	size_t n;
	std::string buf;
	std::cin >> n;
	std::getline(std::cin,buf);
	
	std::regex reg_and("^ *([a-z]+) +AND +([a-z]+) *$");
	std::regex reg_or("^ *([a-z]+) +OR +([a-z]+) *$");
	std::regex reg_not("^NOT +([a-z]+) *$");
	std::regex reg_in("^ *([a-z]+) *$");
	std::smatch sm;

	while(n--){
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
		std::cout << "==========\n";
	}
}

int main(){
	std::ios::sync_with_stdio(false);	
	readText();
	//query();
	return 0;
}