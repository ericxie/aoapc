#include <cstdio>
#include <cstring>


char morse[111][111];
char dict[111][111];

int scnt=0;


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
	int i,k=-1,t,len1,len2,match=0;
	for(i=0;i<scnt;i++) if(strcmp(morse[i],s)==0){
		match++;
		if(k<0) k = i;
		else if(strcmp(dict[i],dict[k])<0) k = i;
	}
	if(match) printf("%s%s",dict[k],match==1?"\n":"!\n");
	else{
		k = -1;
		len1 = strlen(s) ;
		t = 1111;
		for(i=0;i<scnt;i++){
			len2 = strlen(morse[i]);
			if(len1 > len2 && len1 - len2 < t && strncmp(morse[i],s,len2) == 0) k = i,t = len1-len2;
			if(len1 < len2 && len2 - len1 < t && strncmp(morse[i],s,len1) == 0) k = i,t = len2-len1;
		}
		printf("%s?\n",dict[k]);
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
