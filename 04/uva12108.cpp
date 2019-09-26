#include <cstdio>

struct student{
	int a,b,c,d;	
	inline int awake(){
		return c <= a;
	}
	inline int equ(){
		return c == d;
	}
	void next(bool tag){
		if(c==a){
			if(tag) c++;
		} else {
			c++;
			if(c>a+b) c = 1;
		}
	}
}stu[11];

int count(int t,int n){
	int i,s=0;
	for(i=0;i<n;i++) s+= stu[i].awake();
	return s;
}

int main(){
	int i,n,t,k,T=0;
	while(scanf("%d",&n),n){
		printf("Case %d: ",++T);
		for(i=0;i<n;i++) {
			scanf("%d %d %d",&stu[i].a,&stu[i].b,&stu[i].c);
			stu[i].d = stu[i].c;
		}
		for(t=1;;t++){
			int cnt = count(t,n);
			if(cnt == n){
				printf("%d\n",t);
				break;
			}
			k = cnt + cnt < n;
			for(i=0;i<n;i++) stu[i].next(k);
			for(i=k=0;i<n;i++) k+= stu[i].equ();
			if(k==n){
				printf("-1\n");
				break;
			}
		}
	}
	return 0;
}