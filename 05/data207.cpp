#include <bits/stdc++.h>
using namespace std;

unsigned int random(){
	unsigned int r = 0;
	r |= rand();
	r |= rand() << 15;
	r |= (rand()&3) << 30;
	return r; 
}

unsigned int nrand(unsigned int low,unsigned int high){
	unsigned int r;
	r = random()%(high - low + 1);
	return r + low;
}

void percent(){
	double p[70]={0.0};
	int i;
	for(i=0;i<10000;i++) p[nrand(0,30)] += 0.01;
	sort(p,p+70,greater<double>());
	for(i=0;i<70;i++) printf("%f\n",p[i]);
}

int main(){
	freopen("1.in","w",stdout);
	int T = 10,n;
	printf("%d\n\n",T);
	while(T--){
		printf("%.2f\n",nrand(100000,100000000)/100.0);
		percent();
		n = 100;
		printf("%d\n",n);
		while(n--){
			printf("Player %3d%c         ",100-n,nrand(0,5)?' ':'*');
			if(n) {
				switch(nrand(0,15)){
					default:	printf("60 60 60 60\n"); break;
					 case 5:    printf("70 70\n"); break;
					 case 4:	printf("60 60 70 70\n"); break; 
					 case 3: 	printf("60 60 60 DQ\n"); break;
					 case 2: 	printf("60 60 DQ\n"); break;
					 case 1: 	printf("60 DQ\n"); break;
					 case 0: 	printf("DQ\n"); break;    
				}	
			} else printf("60 60 60 59\n");
		}
		if(T) putchar('\n');
	}

	return 0;
}