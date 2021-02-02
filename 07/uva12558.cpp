#include <cstdio>
#include <set>
#include <cstring>

std::set<long long> ban;
long long ans[111];
int flag;
inline long long gcd(long long x,long long y) { return y?gcd(y,x%y):x; }

void dfs(long long a,long long b,long long *c,int k,int d){
	//if(k==0) fprintf(stderr,"%*c%lld %lld %d %d:\n",k<<1|1,'+',a,b,k,d);

	if(k == d){
		//printf("===%d %d %d\n",a,b,c[k-1]);
		if(a == 0){
			if(flag){
				for(int i=k-1;i>=0;i--) {
					if(c[i] == ans[i]) continue;
					else if(c[i] < ans[i]) break;
					else return;
				}
			}
			memcpy(ans,c,sizeof(long long)*d);
			flag = 1;						
		}
		return;
	}
	
	long long start;	
	start = (b+a-1) / a;
	if(k && c[k-1]>= start) start = c[k-1]+1;
	//printf("%d %lld\n",k,start);
	for(long long i=start;;i++) if(ban.find(i)==ban.end()){
		//fprintf(stderr,"%lld = ",i);
		if( i * a > b * (d - k)) break;
		c[k] = i;
		long long na = c[k]*a - b;
		long long nb = c[k]*b;
		long long div = gcd(na,nb);
		na /= div, nb /=div;
		//if(na * (i+1) > nb * (d - k - 1)) break;
		//fprintf(stderr,"%*c%lld %lld : ",(k+1)<<1 | 1,'>',na,nb);
		//for(int i = 0; i<=k; i++) fprintf(stderr,"%lld%c",c[i],",\n"[i==k]);		
		dfs(na,nb,c,k+1,d);	
	}
}

inline void ida(long long a,long long b){
	int d,i;
	long long c[111];
	flag = 0;
	for(d=1;dfs(a,b,c,0,d),!flag;d++);
	printf("%lld/%lld",a,b);
	for(i=0;i<d;i++) printf("%c1/%lld","=+"[i>0],ans[i]);
	putchar('\n');
}

int main(){
	long long a,b,t;
	int k,T,cas=0;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld %d",&a,&b,&k);
		ban.clear();
		while(k--){
			scanf("%lld",&t);
			ban.insert(t);
		}
		printf("Case %d: ",++cas);
		ida(a,b);
	}
	return 0;
}