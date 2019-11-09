#include <cstdio>

int flag;

int build(){
	int wl,dl,wr,dr;
	scanf("%d %d %d %d",&wl,&dl,&wr,&dr);
	if(wl==0) wl = build();
	if(wr==0) wr = build();
	if(wl*dl != wr*dr) flag = 0;
	return wl+wr;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		flag = 1;
		build();
		puts(flag?"YES":"NO");
		if(T) putchar('\n');
	}
	return 0;
}