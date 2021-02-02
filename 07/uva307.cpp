#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <utility>


int item[66];
int vis[66];

int dfs(int curr,int len,int num,int sz,int k,int n){
	if(curr == len) curr = 0, k=0, num++;
	if(num == sz) return 1;	
	while(k<n && (vis[k] || curr + item[k] > len)) k++;
	if(k == n) return 0;
	int i,last;
	for(last = n-1 ; vis[last]; last--);
	int total = 0;
	for(i = k ; i <= last; i++) if(!vis[i]) total += item[i];
	if(curr + total < len) return 0;
	
	//fprintf(stderr,"%d %d | %d %d | %d %d : %d\n",curr,len,num,sz,k,n,item[k]);
	for(i = k; i <= last; i++) if(!vis[i]){
		if(curr + item[i] == len){
			vis[i] = 1;
			if(dfs(0,len,num+1,sz,0,n)) {
				//fprintf(stderr,"%d | %d\n",num,item[i]);
				return 1;
			}
			vis[i] = 0;
			return 0;
		}
		if(!( i != last && curr + item[i] + item[last] > len)){
			vis[i] = 1;
			if(dfs(curr+item[i],len,num,sz,i+1,last+1)) {
				//fprintf(stderr,"%d | %d\n",num,item[i]);
				return 1;
			}
			vis[i] = 0;	
		}		
		if(curr == 0) return 0;
		while(i < last - 1 && item[i+1] == item[i]) i++;
	}	
	return 0; 
}

int main(){
	int n,i,sum;
	while(scanf("%d",&n),n){
		sum = 0;		
		for(i=0;i<n;i++){
			scanf("%d",item+i);
			sum += item[i];
		}
		std::sort(item,item+n,std::greater<int>());

		for(i=item[0];i<=sum;i++) if(sum % i == 0){			
			if(dfs(0,i,0,sum/i,0,n)) {
				memset(vis,0,sizeof(vis));
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}