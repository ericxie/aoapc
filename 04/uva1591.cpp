#include <cstdio>
#include <cmath>
const double eps = 1e-6;

long long getK(long long n,long long p,long long q,long long A,long long B){
	long long off;
	off = (n-1)*p;
	off = (off << A) + off;
	off >>= B;
	off += q;
	return off;
}

long long get(long long n,long long p,long long q,long long &A,long long &B){
	long long t1,t2,len,ans;
	int flag = 1,i,j;
	for(i=0;;i++){
		t1 =  (p<<i)  + p ;
		if(t1 < q) continue;
		j = (log(t1) - log(q)) / log(2) + eps;		
		t2 = q << j;		
		if(t1 >= t2){
			len = getK(n,p,q,i,j);
			if(flag) ans = len,A=i,B=j,flag = 0;
			else {				
				if(len  < ans) ans = len,A=i,B=j;
				else break;
			}			
		}   
	}	
	return ans;
}



int main(){
	long long n,p,q,A,B,K;
	while(scanf("%lld %lld %lld",&n,&p,&q)!=EOF){
		if(n>1) K=get(n,p,q,A,B);
		else K=q,A=B=0;
		printf("%lld %lld %lld\n", K,A,B);
	}
	return 0;
}