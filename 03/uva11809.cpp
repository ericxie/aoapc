#include <cstdio>
#include <cmath>

const double eps = 1e-6;

int main(){
	double a,w1,w2;
	int b,m,e;
	while(scanf("%17lfe%d",&a,&b)==2){
		//printf("%.15f %d\n",a,b);
		w1 = log10(a)+b; 
		for(m=0;m<10;m++){
			for(e=1;e<31;e++){
				w2 = log10(2)*((1<<e)-1) + log10(1 - 1.0 / (1 << (m+1)));
				if(fabs(w1-w2) < eps){
					printf("%d %d\n",m,e);
					goto next;
				}
			}
		}
next: ;
	}
	return 0;
}