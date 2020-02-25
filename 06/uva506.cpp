#include <iostream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <string>
#include <list>

enum Status {uninstall,implicity,explicity};
typedef unsigned int uint;

uint no = 0;

struct Item{
	std::list<std::string> depends;
	uint refs;
	uint ID;
	Status status;
	Item() = default;
};

std::unordered_map<std::string, Item> items;
std::map<int,std::string> installs;

inline void parseDepend(std::string &buf){
	std::stringstream ss;
	ss << buf;
	std::string a,b;
	ss >> a;
	ss >> a;
	while(ss>>b){
		items[a].depends.push_back(b);
	}
}

void install(std::string &name,Status tag){
	if(items[name].status != uninstall) return;
	
	for(auto &x : items[name].depends){
		if(items[x].status == uninstall) install(x,implicity);
	}

	std::cout << "   Installing " << name << "\n"; 
	items[name].ID = ++no;
	installs.emplace_hint(installs.end(),no,name);
	items[name].status = tag;	
	for(auto &x : items[name].depends){
		items[x].refs++;
	}
}

inline void parseInstall(std::string &buf){
	std::stringstream ss;
	ss << buf;
	std::string name;
	ss >> name;
	ss >> name;
	if(items[name].status != uninstall){
		std::cout << "   " << name << " is already installed.\n";
	} else {
		install(name,explicity);		
	}
}

void remove(std::string &name){	
	std::cout << "   Removing " << name << "\n"; 
	items[name].status = uninstall;
	installs.erase(items[name].ID);
	for(auto &x : items[name].depends){
		items[x].refs--;		
		if(items[x].status == implicity && items[x].refs == 0) remove(x);
	}
}

inline void parseRemove(std::string &buf){
	std::stringstream ss;
	ss << buf;
	std::string name;
	ss >> name;
	ss >> name;
	if(items[name].status == uninstall){
		std::cout <<"   " << name << " is not installed.\n";
	} else if(items[name].refs != 0) {
		std::cout <<"   " << name << " is still needed.\n";
	} else {
		remove(name);
	}
}

inline void parseList(){
	for(auto &x : installs){
		std::cout << "   " << x.second << "\n";
	}
}

inline void init(){
	items.clear();
	installs.clear();
	no = 0;
}

int main(){
	std::string buf;
	while(std::getline(std::cin,buf)){
		std::cout << buf << '\n';
		switch(buf[0]){
			case 'E': init(); break;
			case 'D': parseDepend(buf); break;
			case 'I': parseInstall(buf); break;
			case 'R': parseRemove(buf); break;
			case 'L': parseList(); break;
		}			
	}
	return 0;
}