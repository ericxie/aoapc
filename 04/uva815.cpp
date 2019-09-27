#include <cstdio>
#include <cmath>
#include <utility>
int a[33][33],n,m;
const double eps = 1e-6;

double getV(double x,int &k){
	int i,j;
	double v=0.0;
	k = 0;
	for(i=0;i<m;i++) for(j=0;j<n;j++) if(a[i][j] < x){
		k++;
		v += (x - a[i][j]) * 100;
	}
	return v;
}

std::pair<double,double> get(double w){
	double L,R,M,v,percent;
	int k;
	L = -1e6;
	R = 1e6;
	while(fabs(L-R) > eps){
		M = (L + R) / 2.0;
		v = getV(M,k);
		if(v < w) L = M;
		else R = M;
	}
	percent = k * 100.0 / n / m;
	return std::make_pair(M,percent);
}

int main(){
	int i,j,T=0,w;
	while(scanf("%d %d",&n,&m),n){
		for(i=0;i<m;i++) for(j=0;j<n;j++) scanf("%d",&a[i][j]);
		scanf("%d",&w);
		auto ans = get(w);
		printf("Region %d\n",++T);
		printf("Water level is %.2f meters.\n",ans.first);
		printf("%.2f percent of the region is under water.\n\n",ans.second);
	}
	return 0;
}