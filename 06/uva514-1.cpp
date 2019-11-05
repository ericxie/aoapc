#include <cstdio>
#include <stack>

int main(){
	int n,i,j,a[1111],flag;
	while(scanf("%d",&n),n!=0){
		while(scanf("%d",a),a[0]!=0){
			flag = 1;
			for(i=1;i<n;i++) scanf("%d",a+i);
			if(n>2){
				std::stack<int> s;
				int m = a[0];
				for(i=1;i<a[0];i++) s.push(i);
				for(i=1;i<n;i++){
					if(a[i] > m) {
						for(j=m+1;j<a[i];j++) s.push(j);
						m = a[i];
					} else if(a[i] == s.top()) s.pop();
					else{
						flag = 0;
						goto end;
					}
				}
			}
end: 		puts(flag?"Yes":"No");
		}
		putchar('\n');
	}
	return 0;
}