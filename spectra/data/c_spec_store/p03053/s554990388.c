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
int h, w, b[1001][1001], que[1001001], l=0, r=0, dx[]={0,1,0,-1}, dy[]={1,0,-1,0}, ans=0;
char a[1001][1001];

int main(){
	scanf("%d%d", &h, &w);
	for(int i=0; i<h; i++){
		scanf("%s", a[i]);
		for(int j=0; j<w; j++){
			b[i][j] = INF;
			if(a[i][j] == '#'){
				b[i][j] = 0;
				que[r] = i * 10000 + j;
				r++;
				r %= 1001001;
			}
		}
	}
	while(r != l){
		int x=que[l]/10000, y=que[l]%10000;
		l++;
		l %= 1001001;
		for(int i=0; i<4; i++){
			int nx=x+dx[i], ny=y+dy[i];
			if(0<=nx&&nx<h && 0<=ny&&ny<w && a[nx][ny]=='.' && b[nx][ny] > b[x][y] + 1){
				b[nx][ny] = b[x][y] + 1;
				que[r] = nx*10000 + ny;
				r++;
				r %= 1001001;
			}
		}
	}
	for(int i=0; i<h; i++)for(int j=0; j<w; j++)ans = max(ans, b[i][j]);
	printf("%d\n", ans);
	return 0;
}