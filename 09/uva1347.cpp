#include <cstdio>
#include <cmath>
#include <algorithm>
const int N = 1005;
double dp[N][N];
double point[N][2];
double dist[N][N];

inline double getDist(int i,int j){
	double x = point[i][0] - point[j][0] ;
	double y = point[i][1] - point[j][1];
	return sqrt(x*x + y*y);
}

double dfs(int i,int j){	
	
	if(fabs(dp[i][j]) < 1e-6) dp[i][j] = std::min( dfs(i+1,i) + dist[i+1][j], dfs(i+1,j) + dist[i+1][i]);
	//fprintf(stderr,"%d %d : %f %f %f\n",i,j,dp[i][j],dp[i+1][j],dp[i+1][i]);
	return dp[i][j];
}

int main(){
	int i,j,n;
	while(~scanf("%d",&n)) {
		for(i=0;i<n;i++) scanf("%lf %lf",point[i],point[i]+1);
		for(i=0;i<n;i++) for(j=0;j<i;j++) dist[i][j] = getDist(i,j);
		for(i=0;i<n;i++) for(j=0;j<=i;j++) dp[i][j] = 0.0;		
		for(j=0;j<n-2;j++) dp[n-2][j] = dist[n-1][n-2] + dist[n-1][j];			
		printf("%.2f\n",dfs(0,0));
	}
	return 0;
}