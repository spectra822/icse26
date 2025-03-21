/*
  AOJ 2157
  Title:
  @kankichi573
*/
#include <stdio.h>
#include <string.h>
int n;
int min_;

find_not_zero(char *diff,int start)
{
  int i;
  for(i=start;i<n;i++)
    if(diff[i])
      return(i);
  return(-1);
}

is_zero(char *diff)
{
  int i;

  for(i=0;i<n;i++)
    if(diff[i])
      return(0);
  return(-1);
}


void dump(char *diff)
{
  int i;

  for(i=0;i<n;i++)
    printf("%d|",diff[i]);
  printf("\n");
}

void rotate_count(char *diff,int acc)
{
  int i,cnt=0,pos,offs;
  char diff2[10];

  //dump(diff);
  pos=0;
  pos=find_not_zero(diff,pos);

  if(pos==-1)
    {
      if(min_>acc)
	min_=acc;
      return;
    }
  offs=diff[pos];
  memcpy(diff2,diff,10);
  for(i=pos;i<n;i++)
    {
      diff2[i]=diff2[i]+10-offs;
      diff2[i] %= 10;
      rotate_count(diff2,acc+1);
    }
}

void calc_diff(char *init,char *unlock,char *diff,int n)
{
  int i;
  char d;

  for(i=0;i<n;i++)
    {
      d = unlock[i]-init[i];
      if(d<0)
	d+=10;
      diff[i]=d;
    }
}
main()
{
  int i;

  char d,count,st,nn;
  char init[10],unlock[10],diff[10];

  while(scanf("%d",&n) && n)
    {    
      scanf("%s %s",init,unlock);
      if(0==memcmp(init,unlock,n))
            printf("0\n");
      else
	{
	  min_=99;
	  calc_diff(init,unlock,diff,n);
	  rotate_count(diff,0);
	  printf("%d\n",min_);
	}
    }
  return(0);
}