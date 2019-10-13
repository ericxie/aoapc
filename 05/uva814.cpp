#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<std::string,std::unordered_set<std::string> > addr;
const std::string indent = "     ";

void readAddress(){
	std::string city,name;
	int n;
	while(std::cin >> city,city[0]!='*'){
		std::cin >> city >> n;
		std::unordered_set<std::string> names;
		while(n--){
			std::cin >> name;
			names.insert(name);
		}
		addr.emplace(city,names);
	}
}

struct user{
	std::string city,name;
	bool tag;
	user():city(""),name(""),tag(true){}
	user(const std::string &city, const std::string &name):city(city),name(name),tag(true){};
	user(const std::string &s){
		int pos;
		pos = s.find('@');
		name = s.substr(0,pos);
		city = s.substr(pos+1,s.size() - pos);
		tag = true;
	}
	bool operator==(const user &a) const{ return city == a.city && name == a.name;}
	int RcptTo(){
		if(!tag) return 0;
		tag = false;
		std::cout << indent << "RCPT TO:<" << name << '@' << city << ">\n";
		auto it = addr.find(city);
		if(it == addr.end() || it->second.find(name) == it->second.end()){
			std::cout << indent << "550\n";
			return 0;
		}
		std::cout << indent << "250\n";
		return 1;
	}
	void MailFrom(){
		std::cout << indent << "HELO " << city << '\n';
		std::cout << indent << "250\n";
		std::cout << indent << "MAIL FROM:<" << name << '@' << city << ">\n";
		std::cout << indent << "250\n";
	}
	void out(){
		std::cout << city << ',' << name << ',' << tag << '\n';
	}	
};



struct mail{
	user from;
	std::vector<user> to;
	std::vector<std::string > context;
	void out(){
		std::cout << "From:\n";
		from.out();
		std::cout <<"  To:\n";
		for(auto x : to) x.out();
		std::cout <<"Data:\n";	
		for(auto x : context) std::cout << x << '\n';
		std::cout << '\n'; 
	}
	mail(){		
		std::string buf;
		std::cin >> buf;
		if(buf[0]=='*') throw "end";
		from = user(buf);
		to.clear();
		while(std::cin >> buf, buf[0]!='*'){
			user t = user(buf);
			for(auto x : to) if(x == t) goto next;
			to.push_back(t);
			next: ;
		}
		context.clear();
		std::getline(std::cin,buf);
		while(std::getline(std::cin,buf), buf[0]!='*'){
			context.push_back(buf);
		}
	}
	void data(){
		std::cout << indent << "DATA\n";
		std::cout << indent << "354\n";
		for(auto line : context){
			std::cout << indent << line << '\n';
		}
		std::cout << indent << ".\n";
		std::cout << indent << "250\n";			
	}
	void quit(){
		std::cout << indent << "QUIT\n";
		std::cout << indent << "221\n";	
	}
	void process(){
		int c;
		for(auto it = to.begin(); it != to.end(); ++it) if(it->tag){
			std::cout << "Connection between " << from.city << " and " << it->city << '\n';	
			from.MailFrom();
			c = it->RcptTo();
			for(auto it1 = it + 1; it1 != to.end(); ++it1) if(it->city == it1->city){
				c += it1->RcptTo();
			}
			if(c) data();
			quit();
		}
	}
};

int main(){
	readAddress();
	for(;;){
		try{
			mail x;
			//x.out();
			x.process();
		} catch(...){
			return 0;
		}
	}
	return 0;
}
