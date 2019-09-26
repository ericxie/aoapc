#include <cstdio>

char buf[6666];

char disk[6][6666];

void content(int d,int s,int b){
	char *p[6],*q=buf;
	int i,j,k,c=0;
	for(i=0;i<d;i++) p[i] = disk[i];
	for(i=0;i<b;i++) {
		for(k=0;k<d;k++){
			if(k==c) p[k] += s;
			else for(j=0;j<s;j++) *q++ = *p[k]++; 		
		}
		c = (c + 1) % d;
	}
	k = q - buf;
	c = k % 4;
	c = c?4-c:0;
	for(i=0;i<c;i++) *q++='0';
	*q = 0;
	
	for(q=buf;*q;q+=4){
		for(i=0,k=0;i<4;i++) k |= (q[i]-'0') << (3-i);
		printf("%X",k);
	}
	putchar('\n');
}

int main(){
	int i,j,d,s,b,T=0;
	char ch;
	while(scanf("%d",&d),d){
		scanf("%d %d",&s,&b);
		getchar();
		ch = getchar();
		getchar();
		for(i=0;i<d;i++) scanf("%s",disk[i]);
		for(j=0;j<s*b;j++){
			int cnt = 0,s = ch=='O',k;
			for(i=0;i<d;i++) {
				switch(disk[i][j]){
					case '0': s ^= 0; break;
					case '1': s ^= 1; break;
					case 'x': cnt++,k=i; break;
				}
				if(cnt == 2) goto invalid;
				else if(cnt ==1) disk[k][j] = s?'1':'0';
			}
			if(cnt==1) s ^= disk[k][j]=='1';
			if(s) goto invalid;			
		}

		printf("Disk set %d is valid, contents are: ",++T);
		content(d,s,b);
		continue;
invalid:	printf("Disk set %d is invalid.\n",++T);
	}
}