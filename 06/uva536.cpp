#include <cstdio>
#include <cstring>

struct node{
	char c;
	int l,r;
}tree[66];
int cnt;

int build(char *pre,char *mid,int n){
	char *p;
	if(n==0) return 0;
	node *rt = tree + cnt++;
	rt->c = *pre;
	for(p=mid;*p!=*pre;p++);
	rt->l = build(pre+1,mid,p-mid);
	rt->r = build(pre+(p-mid+1),p+1,n-(p-mid+1));
	return rt - tree;
}

void post(int rt){
	if(rt){
		post(tree[rt].l);
		post(tree[rt].r);
		putchar(tree[rt].c);	
	}	
}


int main(){
	char a[33],b[33];
	int n;
	while(~scanf("%s %s",a,b)){
		cnt = 1;
		memset(tree,0,sizeof(tree));
		n = strlen(a);
		build(a,b,n);
		post(1);
		putchar('\n');
	}
	return 0;
}