#include <cstdio>
#include <queue>
#include <unordered_map>

int main(){
	int t,i,n,id,T=0;
	while(scanf("%d",&t),t){
		printf("Scenario #%d\n",++T);
		std::unordered_map<int,int> dict;
		std::queue<int> Q,TQ[t];

		for(i=0;i<t;i++){
			scanf("%d",&n);
			while(n--){
				scanf("%d ",&id);
				dict[id] = i;
			}
		}		

		char buf[111];

		while(gets(buf),buf[0]!='S'){			
			if(buf[0]=='E'){
				sscanf(buf+7,"%d",&id);
				i = dict[id];				
				if(TQ[i].empty()) Q.push(i);
				TQ[i].push(id);
			} else {
				i = Q.front();
				printf("%d\n",TQ[i].front());
				TQ[i].pop();
				if(TQ[i].empty()) Q.pop();
			} 
		}
		putchar('\n');
	}
	return 0;
}