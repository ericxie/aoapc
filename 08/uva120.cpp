#include <cstdio>
#include <cstring>

int str2int(char *buf,int *a){
	int k = 0;
	char *p = strtok(buf," ");
	while(p){
		sscanf(p,"%d",a+k);
		k++;
		p = strtok(NULL," ");
	}
	return k;
}

void rev(int *a,int sz){
	int i,j,t;
	for(i=0,j=sz-1;i<j;i++,j--){
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}

int main(){
	char buf[333];
	while(gets(buf)){
		puts(buf);
		int a[111],i,n,k;
		int sz = str2int(buf,a);
		for(n=sz;n>1;n--){
			for(k=0,i=1; i < n; i++) if(a[i]>a[k]) k = i;			
			if(k==0){
				printf("%d ",sz-n+1);
				rev(a,n);
			} else if( k+1 != n){
				printf("%d %d ",sz-k,sz-n+1);
				rev(a,k+1);
				rev(a,n);

			}			
		}
		printf("0\n");
	}
	return 0;
}