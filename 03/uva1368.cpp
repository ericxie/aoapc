#include <cstdio>
#include <cstring>

int hamming(char *s,char *t){
	int res = 0;
	while(*s&&*t) res += *s++ != *t++;
	return res;
}

int idx(char c){
	const char s[]="ACGT";
	int i;
	for(i=0;i<4&&s[i]!=c;i++);
	return i; 
}

char gao(int *cnt,int &sum){
	int i,k;
	const char s[]="ACGT";
	for(i=0,k=0;i<4;i++){
		sum+=cnt[i];
		if(cnt[i]>cnt[k]) k = i;
	}
	sum -= cnt[k];
	return s[k];
}

int main(){
	int T,n,m,i,j,cnt[1011][4],sum;
	char buf[1011];
	
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		memset(cnt,0,sizeof(cnt));
		for(i=0;i<n;i++){
			scanf("%s",buf);
			for(j=0;j<m;j++) cnt[j][idx(buf[j])]++;
		}
		sum = 0;
		for(i=0;i<m;i++){
			putchar(gao(cnt[i],sum));
		}
		printf("\n%d\n",sum);

	}
	return 0;
}

/*
3
5 8
TATGATAC
TAAGCTAC
AAAGATCC
TGAGATAC
TAAGATGT
4 10
ACGTACGTAC
CCGTACGTAG
GCGTACGTAT
TCGTACGTAA
6 10
ATGTTACCAT
AAGTTACGAT
AACAAAGCAA
AAGTTACCTT
AAGTTACCAA
TACTTACCAA

*/