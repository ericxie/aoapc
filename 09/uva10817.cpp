#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>
#define N 122
const int inf = 1e8;
const int cnt[9] = {1,3,9,27,81,243,729,2187,6561};
int enc[6666];
int dp[N][1<<16];
int te[N][2];

inline void parse(std::string &s,int id){
	int t;
	std::stringstream ss(s);
	ss >> te[id][0];
	te[id][1] = 0;
	while(ss >> t) te[id][1] |= 1 << ((t-1) << 1);
	//fprintf(stderr,"%s : %d : %d , %d\n",s.c_str(),id,te[id][0],te[id][1]);
}

inline int update(int flag,int t,int s){
	int i,mask;
	//fprintf(stderr," %d %d %d -> %d ->",flag,t,s,flag + t);
	flag += t;	
	for(i=0,mask=3,t=1;i<s;i++,mask <<= 2,t<<=2){
		if((flag & mask) == mask) flag ^= t;
	}
	//fprintf(stderr,"%d\n",flag);
	return flag;
}

int encode(int j){
	if(j==0) return j;
	int flag = encode(j/3) << 2;
	flag += j%3;
	return flag; 
}

int main(){
	int i,j,s,m,n,sum,flag;
	std::string str;
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	for(i = 0;i<cnt[8];i++) enc[i] = encode(i);
		
	while(std::cin >> s >> m >> n,s!=0){
		std::getline(std::cin,str);
		for(i=0;i<m+n;i++){
			std::getline(std::cin,str);		
			parse(str,i);
		}
		for(i=0,sum=0,flag=0;i<m;i++) {
			sum += te[i][0];
			flag = update(flag,te[i][1],s);
		}
		for(j=0;j<=n;j++) for(i=0;i<(1<< (s<<1));i++) dp[j][i] = inf;
		dp[0][flag] = sum;
		for(i=1;i<=n;i++){
			for(j=0;j < cnt[s];j++){
				int t1 = enc[j];
				int t2 = update(t1,te[m-1+i][1],s);
				dp[i][t1] = std::min(dp[i][t1],dp[i-1][t1]);
				dp[i][t2] = std::min(dp[i][t2],dp[i-1][t2]);
				dp[i][t2] = std::min(dp[i][t2],dp[i-1][t1] + te[m-1+i][0]);				
				//fprintf(stderr,"%d %d %d , %d %d %d \n",i,t1,t2,dp[i-1][t1],dp[i][t1],dp[i][t2]);
			}
		}
		for(flag=0,i=0;i<s;i++){
			flag <<= 2;
			flag +=2;
		}
		std::cout << dp[n][flag] << "\n";
	}
	return 0;
}