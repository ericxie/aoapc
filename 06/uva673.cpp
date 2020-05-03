#include <stack>
#include <cstdio>

bool solve(char *s){
	std::stack<char> sk;
	while(*s){
		if(*s == ')'){
			if(sk.empty() ||sk.top() != '(') return false;
			sk.pop();
		} else if(*s == ']'){
			if(sk.empty() ||sk.top() != '[') return false;
			sk.pop();
		} else {
			sk.push(*s);
		}
		s++;
	}
	return sk.empty();
}

int main(){
	int n;
	char s[222];
		
	scanf("%d ",&n);
	while(n--){
		gets(s);
		puts(solve(s)?"Yes":"No");
	}
	return 0;
}