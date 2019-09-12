#include <cstdio>
#include <algorithm>

int main(){
	int i,k,x,y;
	for(;;){
		int rects[6][3]={0};
		int cnt=0;
		for(k=0;k<6;k++) {			
			if(scanf("%d %d",&x,&y)==EOF) return 0;
			if(x<y) std::swap(x,y);
			for(i=0;i<cnt;i++) {
				if(rects[i][0]==x && rects[i][1] == y) {
					rects[i][2]++;
					break;
				}
			}
			if(i==cnt) 	rects[i][0] = x,rects[i][1] = y,rects[i][2] = 1,cnt++;
		}
		int flag = 0;
		switch(cnt){
			case 1 : 
				flag = rects[0][0] == rects[0][1];
				break;
			case 2:
				if((rects[0][2] == 4 && rects[1][0] == rects[1][1] && (rects[1][0] == rects[0][0] || rects[1][0] == rects[0][1])) ||
				   (rects[1][2] == 4 && rects[0][0] == rects[0][1] && (rects[0][0] == rects[1][0] || rects[0][0] == rects[1][1])))
						flag = 1;
				break;
			case 3:
				if(rects[0][2] == 2 && rects[1][2] == 2 && rects[2][2] == 2) {
					int edges[6];
					for(i=0;i<3;i++) edges[i<<1] = rects[i][0], edges[i<<1|1] = rects[i][1];
					std::sort(edges,edges+6);
					for(i=0;i<3;i++) if(edges[i<<1] != edges[i<<1 | 1]) goto end;
					flag = 1;				
				}
				break;
		}
end:	puts(flag?"POSSIBLE":"IMPOSSIBLE");
	} 
	return 0;
}