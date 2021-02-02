#include <cstdio>
#include <stack>
#include <utility>
#include <cctype>

int token(char * &s){
	int val = 0;
	if(isdigit(*s)){		
		for(val=0; isdigit(*s); s++){
			val *= 10;
			val += *s - '0';
		}
	} else {		
		val = -(*s++); 
	}
	return val;
}

std::stack<int> ns;
std::stack<char> os;

int calc(){
	int a,b,r;
	char op;
	a = ns.top(), ns.pop();
	b = ns.top(), ns.pop();
	op = os.top(), os.pop();
	if(op == '+') r = b+a;
	else if(op == '-') r = b-a;
	else r = b*a;
	//fprintf(stderr,"%d %c %d = %d\n",b,op,a,r);
	ns.push(r);
	return r;
	
}

int eval(char * const s){
	
	char *p = s;
	int val;
	
	while(!ns.empty()) ns.pop();
	while(!os.empty()) os.pop();	
	for(;;){
		val = token(p);
		//fprintf(stderr,"  %s: %d : %c\n",p,val,os.empty()?'#':os.top());		

		if(val>=0)	ns.push(val);
		else{
			val = -val;
			switch(val){
				case '+':
				case '-':
					while(!os.empty()) calc();						
					os.push(val);
					break;
				case '*':
					while(!os.empty() && os.top() == '*') calc();
					os.push(val);
					break;
				case '=':					
					while(!os.empty()) calc();
					return ns.top();
			}
		}
	}
	return -1;
}

const char ops[]="+-*";
int flag;

void dfs(char *s,char *t,int p,int q,int tag){	
	if(s[p+1] == '='){
		if(p==q) return;
		t[q] = s[p];
		t[q+1] = s[p+1];
		t[q+2] = 0;
		//fprintf(stderr,"%s\n",t);

		if(eval(t) == 2000){
			flag = 1;
			printf("  %s\n",t);
		}
		return;
	}
	if(tag){
		t[q] = s[p];
		dfs(s,t,p+1,q+1,1);
	}
	for(int i=0; i<3; i++){
		t[q] = s[p];
		t[q+1] = ops[i];
		dfs(s,t,p+1,q+2,s[p+1]!='0');
	}	
}

int main(){
	char s[11],t[22];
	int T=0;
	
	while(gets(s),s[0]!='='){
		printf("Problem %d\n",++T);
		flag = 0;
		dfs(s,t,0,0,s[0]!='0');
		if(!flag) puts("  IMPOSSIBLE");
	}
	return 0;
}