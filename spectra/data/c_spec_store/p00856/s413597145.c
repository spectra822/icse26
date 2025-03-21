/*
  AOJ 1277
  Title:Minimal Backgammon
  @kankichi573
*/
#include <stdio.h>
#include <string.h>
#include <float.h>
#define ONE_SIXTH (1.0/6.0)

int N,T,L,B;
int sq[100];
double memo[101][101];

int myabs(int x)
{
  return (x>=0)?x:(-x);
}

double solve(int rest,int turn)
{
  int i,next_pos;
  double ret;

  if(memo[rest][turn]!=DBL_MAX)
    ret=memo[rest][turn];
  else if(rest==0)
    ret=1.0;
  else if(turn<=0)
    ret=0.0;
  else if(turn==1 && rest<=6)
    ret=ONE_SIXTH;
  else
    for(i=1,ret=0.0;i<=6;i++)
      {
	next_pos=myabs(rest-i);
	if(sq[N-next_pos]==0)
	  ret += ONE_SIXTH * solve(next_pos,turn-1);
	else if(sq[N-next_pos]=='L')
	  ret += ONE_SIXTH * solve(next_pos,turn-2);
	else if(sq[N-next_pos]=='B')
	  ret += ONE_SIXTH * solve(N,turn-1);
      }
  //printf("%d %d :%lf\n",rest,turn,ret);
  memo[rest][turn]=ret;
  return(ret);
}
main()
{
  int i,j,l,b;
  double ret;
  while(scanf("%d %d %d %d",&N,&T,&L,&B)  && (N||T||L||B))
    {

      memset(sq,0,sizeof(sq));
      for(i=0;i<=100;i++)
	{
	  for(j=0;j<=100;j++)
	    memo[i][j]=DBL_MAX;
	}

      for(i=0;i<L;i++)
	{
	  scanf("%d",&l);
	  sq[l]='L';
	}
      for(i=0;i<B;i++)
	{
	  scanf("%d",&l);
	  sq[l]='B';
	}
      ret=solve(N,T);
      printf("%lf\n",ret);
    }
  return(0);
}