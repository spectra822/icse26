#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<tgmath.h>
#include<stdbool.h>
#include<sys/queue.h>
#include<time.h>
#define ll long long
#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1001001001;
int h, w, k, s[2], g[2], dx[]={1,0,-1,0}, dy[]={0,1,0,-1}, que[1001001][2], r=0, l=0;

int main(){
    scanf("%d%d%d", &h, &w, &k);
    scanf("%d%d%d%d", &s[0], &s[1], &g[0], &g[1]);
    s[0]--;s[1]--;g[0]--;g[1]--;
    char c[h+5][w+5];
    int d[h][w];
    for(int i=0; i<h; i++){
        scanf("%s", c[i]);
        for(int j=0; j<w; j++)d[i][j] = INF;
    }
    que[r][0] = s[0]; que[r][1] = s[1]; r++; r%=1001001;
    d[s[0]][s[1]] = 0;
    while(r != l){
        int x = que[l][0], y = que[l][1]; l++; l%=1001001;
        for(int i=0; i<4; i++){
            for(int j=1; j<=k; j++){
                if(0<=x+j*dx[i] && x+j*dx[i]<h && 0<=y+j*dy[i] && y+j*dy[i]<w && c[x+j*dx[i]][y+j*dy[i]]=='.' && d[x+j*dx[i]][y+j*dy[i]] >= d[x][y]+1){
                    if(d[x+j*dx[i]][y+j*dy[i]] == d[x][y]+1)continue;
                    d[x+j*dx[i]][y+j*dy[i]] = d[x][y] + 1;
                    que[r][0] = x+j*dx[i]; que[r][1] = y+j*dy[i]; r++; r%=1001001;
                    //printf("%d %d %d\n", que[r-1][0], que[r-1][1], d[x][y]+1);
                }else break;
            }
        }
    }
    if(d[g[0]][g[1]] == INF)d[g[0]][g[1]] = -1;
    printf("%d\n", d[g[0]][g[1]]);
    //for(int i=0; i<h; i++){for(int j=0; j<w; j++){if(j)putchar(32);printf("%d", d[i][j]);}putchar(10);}
    return 0;
}
