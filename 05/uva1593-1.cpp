#include <cstdio>
#include <cstring>
const int N = 1000;
const int M = 200;
int width[M];
int col[N];
char *ss[N][M];
char lines[N][M];

int main(){
    int i,n = 0,j,len;
    while(gets(lines[n])){
        j = 0;
        char *p = strtok(lines[n]," ");
        while(p!=NULL){
            ss[n][j] = p;
            len = strlen(p);
            if(len > width[j])  width[j] = len;
            p = strtok(NULL," ");            
            j++;
        }
        col[n++] = j;
    }
    for(i=0;i<n;i++){
        for(j=0;j<col[i]-1;j++) printf("%-*s",width[j]+1,ss[i][j]);
        if(col[i]) printf("%s",ss[i][j]);
        putchar('\n');
    }
    return 0;
}