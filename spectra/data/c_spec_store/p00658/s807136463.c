#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_MODE 0

#define GAMEOVER_CLEAR	1
#define GAMEOVER_HOLE	2
#define GAMEOVER_BLOCK	3
#define GAMEOVER_WGOAL	4

int width,height;
char map[51][51];

int px,py;
int gx,gy;
int gameover;

void game_init(void) {
	int x,y;
	for(y=0;y<height;y++) {
		for(x=0;x<width;x++) {
			if(map[y][x]=='S') {
				px=x;py=y;
				map[y][x]='.';
			} else if(map[y][x]=='G') {
				gx=x;gy=y;
			}
		}
	}
	for(x=0;x<width;x++)map[height][x]='#';
	gameover=0;
}

void moveto(int to) {
	int old_px=px;
	int i;
	int add;
	if(to<1 || to>width)return;
	to--;
	add=(to<px)?-1:1;
	if(map[py][to]!='.')return;
	if(px==to)return;
	for(i=px;i!=to;i+=add) {
		if(map[py+1][i]=='.')break;
	}
	if(i==to && map[py+1][to]!='.') {
		px=to;
		/* countdown */
		if(map[py+1][old_px]=='3') {
			map[py+1][old_px]='2';
		} else if(map[py+1][old_px]=='2') {
			map[py+1][old_px]='1';
		} else if(map[py+1][old_px]=='1') {
			map[py+1][old_px]='.';
		}
	}
}

void push_internal(int x,int y,int isright) {
	int i;
	char block=map[y][x];
	if(block=='C' || block=='.')return;
	map[y][x]='.';
	if(isright) {
		if(x<width-1 && map[y][x+1]!='.') {
			map[y][x]=block;return;
		}
		for(i=x+1;i<width;i++) {
			if(!(block=='I' || map[y+1][i]=='I') ||
				map[y+1][i]=='.')break;
			if(i<width-1 && map[y][i+1]!='.')break;
		}
		if(i<width)map[y][i]=block;
	} else {
		if(x>0 && map[y][x-1]!='.') {
			map[y][x]=block;return;
		}
		for(i=x-1;i>=0;i--) {
			if(!(block=='I' || map[y+1][i]=='I') ||
				map[y+1][i]=='.')break;
			if(i>0 && map[y][i-1]!='.')break;
		}
		if(i>=0)map[y][i]=block;
	}
}

void push(int isright) {
	int i;
	if(isright) {
		if(px>=width-1)return;
		if(map[py][px+1]=='.')return;
		for(i=px+1;i<width && map[py][i]!='.';i++) {
			if(map[py][i]=='C')return;
		}
		for(i--;i>px;i--)push_internal(i,py,1);
	} else {
		if(px<=0)return;
		if(map[py][px-1]=='.')return;
		for(i=px-1;i>=0 && map[py][i]!='.';i--) {
			if(map[py][i]=='C')return;
		}
		for(i++;i<px;i++)push_internal(i,py,0);
	}
}

void pull(int isright) {
	int old_px=px;
	if(px<=0 || px>=width-1)return;
	if(isright) {
		if(map[py][px+1]=='.' && map[py][px-1]!='.' &&
				map[py][px-1]!='C') {
			map[py][px]=map[py][px-1];
			map[py][px-1]='.';
			px++;
		} else return;
	} else {
		if(map[py][px-1]=='.' && map[py][px+1]!='.' &&
				map[py][px+1]!='C') {
			map[py][px]=map[py][px+1];
			map[py][px+1]='.';
			px--;
		} else return;
	}
	/* countdown */
	if(map[py+1][old_px]=='3') {
		map[py+1][old_px]='2';
	} else if(map[py+1][old_px]=='2') {
		map[py+1][old_px]='1';
	} else if(map[py+1][old_px]=='1') {
		map[py+1][old_px]='.';
	}
}

void climb(int isright) {
	int old_px=px;
	if(py<=0)return;
	if(isright) {
		if(px<width-1 && map[py-1][px]=='.' &&
				map[py-1][px+1]=='.' && map[py][px+1]!='.') {
			px++;
			py--;
		} else return;
	} else {
		if(px>0 && map[py-1][px]=='.' &&
				map[py-1][px-1]=='.' && map[py][px-1]!='.') {
			px--;
			py--;
		} else return;
	}
	/* countdown */
	if(map[py+2][old_px]=='3') {
		map[py+2][old_px]='2';
	} else if(map[py+2][old_px]=='2') {
		map[py+2][old_px]='1';
	} else if(map[py+2][old_px]=='1') {
		map[py+2][old_px]='.';
	}
}

void getdown(int isright) {
	int old_px=px;
	if(isright) {
		if(px<width-1 && map[py][px+1]=='.' && map[py+1][px+1]=='.') {
			px++;
			py++;
		} else return;
	} else {
		if(px>0 && map[py][px-1]=='.' && map[py+1][px-1]=='.') {
			px--;
			py++;
		} else return;
	}
	/* countdown */
	if(map[py][old_px]=='3') {
		map[py][old_px]='2';
	} else if(map[py][old_px]=='2') {
		map[py][old_px]='1';
	} else if(map[py][old_px]=='1') {
		map[py][old_px]='.';
	}
}

int gameover_hantei(void) {
	if(gameover)return gameover;
	if(map[py+1][px]=='G')return gameover=GAMEOVER_CLEAR;
	if(map[py+1][px]=='B')return gameover=GAMEOVER_HOLE;
	if(map[py][px]!='.')return gameover=GAMEOVER_BLOCK;
	if(map[gy][gx]!='G')return gameover=GAMEOVER_WGOAL;
	return 0;
}

void auto_syori(void) {
	int x,y,y2;
	int moved=1;
	while(moved) {
		moved=0;
		for(y=0;y<height;y++) {
			for(x=0;x<width;x++) {
				if(map[y+1][x]=='B' && map[y][x]!='.') {
					map[y][x]='.';
					moved=1;
				}
			}
		}
		while(map[py+1][px]=='.') {
			py++;
			moved=1;
		}
		for(y=height-2;y>=0;y--) {
			for(x=0;x<width;x++) {
				if(map[y][x]!='.') {
					y2=y;
					while(1) {
						if((x<=0 || map[y2+1][x-1]=='.') &&
								map[y2+1][x]=='.' &&
								(x>=width-1 || map[y2+1][x+1]=='.')) {
							moved=1;
						} else break;
						y2++;
					}
					if(y2!=y) {
						map[y2][x]=map[y][x];
						map[y][x]='.';
					}
				}
			}
		}
	}
}

int main(void) {
	int i;
	int command_num;
	char command[100];
	char command2[100];
	while(1) {
		scanf("%d%d",&height,&width);
		if(height==0 && width==0)break;
		for(i=0;i<height;i++)scanf("%s",map[i]);
		scanf("%d",&command_num);
		game_init();
		for(i=0;i<command_num;i++) {
			scanf("%s%s",command,command2);
			if(!gameover_hantei()) {
				if(strcmp(command,"MOVETO")==0) {
					moveto(atoi(command2));
				} else if(strcmp(command,"PUSH")==0) {
					push(command2[0]=='R');
				} else if(strcmp(command,"PULL")==0) {
					pull(command2[0]=='R');
				} else if(strcmp(command,"GETDOWN")==0) {
					getdown(command2[0]=='R');
				} else if(strcmp(command,"CLIMB")==0) {
					climb(command2[0]=='R');
				} else return 1;
				if(!gameover_hantei())auto_syori();
#if DEBUG_MODE
				{
					char block=map[py][px];
					int j;
					if(block=='.')map[py][px]='S';
					for(j=0;j<height;j++)puts(map[j]);
					map[py][px]=block;
				}
				if(gameover_hantei())break;
#endif
			}
#if DEBUG_MODE
			else break;
#endif
		}
		switch(gameover_hantei()) {
			case GAMEOVER_CLEAR:
				puts("Game Over : Cleared");
				break;
			case GAMEOVER_HOLE:
				puts("Game Over : Death by Hole");
				break;
			case GAMEOVER_BLOCK:
				puts("Game Over : Death by Block");
				break;
			case GAMEOVER_WGOAL:
				puts("Game Over : Death by Walking Goal");
				break;
			default:
				puts("Game Over : Gave Up");
				break;
		}
	}
	return 0;
}