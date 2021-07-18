#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
 
int main
{
    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random mean between 1 and 6
    std::mt19937_64 e1(r());
    int radix =1 << 28;
    freopen("1152.in","w",stdout);
    std::uniform_int_distribution<int> uniform_dist(-radix, radix);    
    int T = 10;
    printf("%d\n",T);
    while(T--){
    	int n = 4000;
    	printf("%d\n",n);
    	for(int i=0;i<n;i++){
    		printf("%d %d %d %d\n",uniform_dist(e1),uniform_dist(e1),uniform_dist(e1),uniform_dist(e1));
    	}
    }
    return 0;
}