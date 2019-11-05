#include <cstdio>

int main(){
	int n,i,j,k,a[1111],flag;
	while(scanf("%d",&n),n!=0){
		while(scanf("%d",a),a[0]!=0){
			flag = 1;
			for(i=1;i<n;i++) scanf("%d",a+i);
			if(n>2){
				for(i=0;i<n-2;i++) for(j=i+1;j<n-1;j++) if(a[i]>a[j]+1) {
					for(k=j+1;k<n;k++) if(a[j] < a[k] && a[k] < a[i]) {
						flag= 0 ;
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