#include <cstdio>
#include <algorithm>

inline long long gcd(long long x,long long y){
	long long r;
	while(y){
		r = x % y;
		x = y;
		y = r;
	}
	return x;
}

inline long long lcm(long long x,long long y){
	return x / gcd(x,y) * y;
}

int main(){
	int T,i,cas=0;
	long long cap,t,k,period,n,v,s1,v1,s2,v2;
	scanf("%d",&T);
	
	while(T--){		
		scanf("%lld %lld %lld %lld %lld",&cap,&s1,&v1,&s2,&v2);
		v = 0;
		period = lcm(s1,s2);
		n = cap / period;
		if(n>1) {
			v += (n - 1) * std::max( period / s1 * v1, period / s2 * v2);
			cap -= (n - 1) * period;
		} 		
		//fprintf(stderr,"%lld %lld %lld\n",n,period,v);
	
		k = 0;
		if(s1 < s2) std::swap(s1,s2), std::swap(v1,v2);
		for(i=0;i*s1<=cap; i++){
			t = i * v1 + (cap - i*s1) / s2 * v2;
			if(t > k) k = t; 
		}
		//fprintf(stderr,"%lld %lld\n",n,k);
		v += k;
		
		printf("Case #%d: %lld\n",++cas,v);
	}
}