#include <cstdio>
#include <cstring>
const int N = 729;
const int ro[3][6]={{1,3,5,2,4,6},{5,1,3,4,6,2},{4,2,1,6,5,3}};
int a[N];
int type;

int getID(char *s){
	int i,j,r = 0;
	const char c[]="bgr";
	for(i=0;i<6;i++){
		r *= 3;
		for(j=0;j<3 && c[j]!=s[i];j++);
		r += j;
	}
	return r;
}

char * getStr(int id,char *s){
	int i;
	const char c[]="bgr";
	for(i=5;i>=0;i--){
		s[i] = c[id % 3] ;
		id /= 3;
	}
	s[6] = 0;
	return s;
}

void dfu(int u){
	int i,j,v;
	char s[7],ns[7];
	if(a[u]) return;
	a[u] = type;
	getStr(u,s);
	//printf("%d %s\n",a[u],s);
	for(i=0;i<3;i++){
		for(j=0;j<6;j++) ns[j] = s[ro[i][j]-1];
		v = getID(ns);
		dfu(v);
	}
}

void dfs(){
	int i;
	memset(a,0,sizeof(a));
	for(i=0;i<N;i++) if(!a[i]){
		++type;
		dfu(i);
	}
}

int main(){
	char s[22],s1[7],s2[7];
	int id1,id2;
	dfs();
	while(gets(s)){
		strncpy(s1,s,6);
		s1[6] = 0;
		strncpy(s2,s+6,6);
		s2[6] = 0;
		id1 = getID(s1);
		id2 = getID(s2);
		//printf("%s %d %d,%s %d %d\n",s1,id1,a[id1],s2,id2,a[id2]);
		puts(a[id1]==a[id2]?"TRUE":"FALSE");
	}
	return 0;
}

