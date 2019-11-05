#include <cstdio>
#include <cstring>
#include <unordered_map>

const unsigned int MAX_LEN = 1111;
const unsigned int MAX_LINES = 1505;
const unsigned int MAX_TEXTS = 111;
const unsigned int N = (MAX_LINES >> 8) + 1;

char text[MAX_TEXTS][MAX_LEN];
int limit[MAX_TEXTS];
int n_text;

struct BITS{
	unsigned long long bits[N];
	BITS(){ memset(bits,0,sizeof(bits)); }
	BITS(const BITS &a){ memcpy(bits,a.bits,sizeof(bits)); }
	inline void set(unsigned int idx){
		unsigned int offset = idx >> 8;
		unsigned int pos = idx & 0x3f;		
		bits[offset] |= (1ULL << pos); 

	}	
	inline void bit_or(const BITS &rhs){
		for(unsigned int i = 0; i < N; i++) bits[i] |= rhs.bits[i];
	}
	inline void bit_not(){
		for(unsigned int i = 0; i < N; i++) bits[i] = ~bits[i];
	}
	inline bool at(unsigned int idx) const{
		unsigned int offset = idx >> 8;
		unsigned int pos = idx & 0x3f;
		return (bits[offset] & (1ULL << pos)) != 0ULL; 	
	}
	bool any(unsigned int left,unsigned int right){
		unsigned int left_idx = left >> 8;
		unsigned int left_pos = left & 0x3f;
		unsigned int right_idx = right >> 8;
		unsigned int right_pos = right & 0x3f;
		for(unsigned int  i = left_idx + 1 ;  i < right_idx; ++i) if(bits[i]) return true;
		unsigned long long mask;
		if(left_idx == right_idx){
			mask = ~0ULL;
			mask ^= (1ULL << left_pos) - 1;
			mask ^=  ~((1ULL << right_pos) - 1);
			if(bits[left_idx] & mask) return true;
		} else {
			mask = ~0ULL << left_pos;
			if(bits[left_idx] & mask) return true;
			mask = (1ULL << right_pos) - 1;
			if(bits[right_idx] & mask) return true;	
		}		
		return false;
	}
	void out(unsigned int id,bool &flag){	
		if(flag) puts("----------"),flag = false;
		for(int i = limit[id] ; i< limit[id+1]; ++i){
			if(at(i)) {				
				printf("%s\n",text[i]);
				flag  = true;
			}
		}
	}
};

std::unordered_map<std::string,BITS> bitmap;

BITS get(const std::string &s){
	auto it = bitmap.find(s);
	if(it == bitmap.end()){
		BITS t;
		return t;
	} else {
		return it->second;
	}
}

void parse(char *s,int line){
	char *p;
	for(p=s;*p;p++){
		if(*p>='A' && *p <='Z') *p += 'a' - 'A';
		else if(*p <'a' || *p >='z') *p = ' ';
	}
	p = strtok(s," ");
	while(p){		
		std::string word(p);
		if(word != "the" && word !="a" && word !="to" && 
		   word != "and" && word != "or" && word != "not") {
			auto it = bitmap.find(word);
			if(it == bitmap.end()){
				BITS t;
				t.set(line);	
				bitmap.emplace(word,t);
			} else {
				it->second.set(line);
			}	
		}		
		p = strtok(0," ");
	}
}

void readText(){
	char buf[1111];
	int id = 0,line = 0;
	scanf("%d ",&n_text);
	for(id = 0; id < n_text;){
		gets(buf);
		if(strcmp(buf,"**********") == 0) limit[++id] = line;
		else {
			strcpy(text[line],buf);
			parse(buf,line);
			++line;	
		}		
	}	
}

void AND(const std::string &word1,const std::string &word2,bool &flag){
	BITS a = get(word1);
	BITS b = get(word2);
	BITS c(a);
	c.bit_or(b);			
	for(int i = 0; i < n_text; i++){
		if(a.any(limit[i],limit[i+1]) && b.any(limit[i],limit[i+1])) c.out(i,flag);
	}
}

void OR(const std::string &word1,const std::string word2,bool &flag){
	BITS a = get(word1);
	BITS b = get(word2);
	a.bit_or(b);
	for(int i = 0; i< n_text; i++){
		if(a.any(limit[i],limit[i+1])) a.out(i,flag);
	}
} 

void NOT(const std::string &word,bool &flag){
	BITS a = get(word);
	BITS b(a);
	b.bit_not();
	for(int i = 0; i< n_text; i++){
		if(!a.any(limit[i],limit[i+1]))	b.out(i,flag);
	}
}

void IN(const std::string &word,bool &flag){
	BITS a = get(word);
	for(int i = 0; i< n_text; i++){
		if(a.any(limit[i],limit[i+1])) a.out(i,flag);
	}	
}

void  query(){
	int n,t;
	char buf[111],word[3][MAX_LEN];
	scanf("%d ",&n);
	while(n--){
		gets(buf);
		bool flag = false;		
		t = sscanf(buf,"%s %s %s",word[0],word[1],word[2]);
		if(t==1) IN(std::string(word[0]),flag);
		else if(t==2) NOT(std::string(word[1]),flag);
		else if(word[1][0]=='A') AND(std::string(word[0]),std::string(word[2]),flag);
		else OR(std::string(word[0]),std::string(word[2]),flag);
		if(!flag) puts("Sorry, I found nothing.");
		puts("==========");
	}
}

int main(){
	readText();
	//query();
}
