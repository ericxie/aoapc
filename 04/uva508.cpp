#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
struct node{
	bool word;
	bool multi;
	int sid;
	int next[2];
}trie[111111];

int ncnt = 1;

char morse[111][111];
char dict[111][111];

int scnt=0;

void insert(int nid,int sid,int k){
	node *p = trie+nid;
	
	if(morse[sid][k]){
		int d = morse[sid][k] == '.';
		if(!(p->next[d])) p->next[d] = ++ncnt;
		insert(p->next[d],sid,k+1); 	
	} else {
		if(p->word){
			p->multi = true;
			if( strcmp(dict[sid],dict[p->sid]) < 0) {
				p->sid = sid;
			}			
		} else {
			p->word = true;
			p->sid = sid;
		}
	}
	//printf("%d %d %d : %d %d %s : %d %d\n",nid,p->word,p->multi,sid,k,morse[sid],p->next[0],p->next[1]);	
}

int find(int nid,int n){
	node *p;
	std::queue<std::pair<int,int> > Q;
	Q.emplace(nid,1);
	while(!Q.empty()){
		auto qt = Q.front();
		Q.pop();
		p = trie+ qt.first;
		if(p->word) return p->sid;
		if(qt.second < n){
			if(p->next[0]){
				Q.emplace(p->next[0],qt.second+1);
			}
			if(p->next[1]){
				Q.emplace(p->next[1],qt.second+1);
			}
		} 
	}
	return -1;		
}

char tab[111][111];
int tcnt = 0;

void s2m(char *s,char *m){
	int i;
	char *p;
	while(*s){
		for(i=0;i<tcnt && tab[i][0] != *s;i++);
		p = tab[i];
		p++;
		while(*p) *m++ = *p++;	
		s++;
	}
	*m = 0;
}

void solve(char *s){
	int nid = 1,k,n,i=0,lp=-1,ls=-1;
	
	node * p = trie + 1; 
	while(s[i]){		
		int d = s[i] == '.';	
		//printf("%s %c %d : %d\n",s,s[i],d,p->next[d]);
		if(p->next[d]){
			nid = p->next[d];
			p = trie + nid;	
			if(p->word) lp = i,ls = p->sid;	
			i++;	
		} else break; 
		
	}
	//printf("  %d %d %d %d %d %d,%d %d\n",nid,p->word,p->multi,p->sid,p->next[0],p->next[1],lp,ls);
	if(!s[i] && p->word){
		printf("%s%s",dict[p->sid],p->multi?"!\n":"\n");
	} else {
		if(lp>=0) n = strlen(s) - lp -1;
		else n = 100;
		k = find(nid,n);
		if(k!=-1) ls = k;
		printf("%s?\n",dict[ls]); 	
	}	
}

void readTab(){
	char buf[222];
	while(scanf("%s",buf),buf[0]!='*'){
		tab[tcnt][0] = buf[0];
		scanf("%s",buf);
		strcpy(tab[tcnt]+1,buf);
		//puts(tab[tcnt]);
		tcnt++; 
	}
}

void readDict(){
	char buf[222],mo[222];

	while(scanf("%s",buf),buf[0]!='*'){
		strcpy(dict[scnt],buf);
		s2m(buf,mo);
		strcpy(morse[scnt],mo);
		//printf("%s %s\n",dict[scnt],morse[scnt]);		
		insert(1,scnt,0);		
		scnt++;
	}
}

void decode(){
	char buf[222];
	while(scanf("%s",buf),buf[0]!='*'){
		//puts(buf);
		solve(buf);
	}
}

int main(){
	readTab();
	readDict();
	decode();
	return 0;
}
