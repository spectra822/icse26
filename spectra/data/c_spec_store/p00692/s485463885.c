/*
  AOJ 1110
  Title:Patience
  @kankichi573
*/
#include <stdio.h>
#include <string.h>
#define max(x,y) (((x)>(y))?(x):(y))
int max_;
char buf[20];

void remove2(char cards[],char out[],int m1,int m2)
{
  int i,j;
 
  //printf("rm %d %d\n",m1,m2);

  for(i=j=0;i<20;i++)
    {
      if(i != m1 && i!= m2)
	{
	  out[j]=cards[i];
	  j++;
	}
    }
}
void dump(char buf[],int depth)
{
  int i,j;
  for(i=0;i<5;i++)
    {
      for(j=0;j<4;j++)
	{
	  if(i*4+j >= 20-depth*2)
	    goto END;
	  printf("%d|",buf[i*4+j]);
	}
      if(i<4)
	printf("\n");
    }
 END:
  printf("\n------- [%d]\n",depth);
  return;
}
int solve(char buf[],int depth)
{
  int  i,last_;
  char mybuf[4][20];


  last_=20-2*depth;
#ifdef DEBUG
  dump(buf,depth);
#endif
  for(i=0;i<last_;i++)
    {
      if(i < 16 && i+4 < last_ && buf[i]==buf[i+4])
	{
	  remove2(buf,&mybuf[0][0],i,i+4);
	  solve(&mybuf[0][0],depth+1);
	}
      if((i % 4)< 3 && i+1 < last_ && buf[i]==buf[i+1])
	{
	  remove2(buf,&mybuf[1][0],i,i+1);
	  solve(&mybuf[1][0],depth+1);
	}
      if(i < 16 && (i % 4)< 3 && i+5 < last_ && buf[i]==buf[i+5])
	{
	  remove2(buf,&mybuf[2][0],i,i+5);
	  solve(&mybuf[2][0],depth+1);
	}
      if(i < 16 && (i % 4)> 0 && i+3 < last_ && buf[i]==buf[i+3])
	{
	  remove2(buf,&mybuf[3][0],i,i+3);
	  solve(&mybuf[3][0],depth+1);
	}
    }
  max_=max(max_,depth);
}

main()
{
  
  int i,j,n,ret;

  scanf("%d ",&n);
  for(i=0;i<n;i++)
    {
      for(j=0;j<20;j++)
	{
	  scanf("%c ",&buf[j]);
	  buf[j] -= '0';
	}
      max_=0;
      ret=solve(buf,0);
      printf("%d\n",20-max_*2);
    }
  return(0);
}