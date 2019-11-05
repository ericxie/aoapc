#include <cstdio>
#include <unordered_map>
#include <string>
#include <cstring>
const long long width = 100000LL;
int main(){
	int row,i,j,n,m;
	while(scanf("%d %d ",&n,&m)!=EOF){
		std::unordered_map<std::string,int> dict;
		std::unordered_map<long long,int> hash;
		char buf[1111],*tok;
		int idx[m],k,id,flag = 0;
		for(row=0;row<n;row++){
			gets(buf);
			if(flag) continue;
			tok = strtok(buf,",");
			k = 0;
			while(tok){
				std::string s(tok);
				if(dict.count(s)==0) dict[s] = id = dict.size();
				else id = dict[s];
				idx[k++] = id;
				tok = strtok(0,",");
			}
			for(i=0;i<k-1;i++) for(j=i+1;j<k;j++){
				long long t;
				t = i * 10 * width * width + j * width * width + idx[i] * width + idx[j];
				auto it = hash.find(t);
				if(it == hash.end()) hash.emplace(t,row);
				else {
					printf("NO\n%d %d\n%d %d\n",it->second+1,row+1,i+1,j+1);
					flag = 1;
					goto next;
				}
			}
			next: ;
		}
		if(!flag) puts("YES");		
	}
	return 0;
}