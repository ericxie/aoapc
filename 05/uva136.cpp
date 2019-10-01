#include <cstdio>

int main(){
	int q[1501],head[3],tail,t,c[3]={2,3,5},i,k;
	head[0] = head[1] = head[2] = tail = 0;
	q[tail++] = 1;
	while(tail < 1500){
		for(k=0,i=0;i<3;i++){
			if(q[head[i]]*c[i] < q[head[k]]*c[k]) k = i;
		}
		t = q[head[k]]*c[k];
		head[k]++; 
		if(t > q[tail-1]) q[tail++] = t; 
	}
	printf("The 1500'th ugly number is %d.\n",q[tail-1]);
	return 0;
}