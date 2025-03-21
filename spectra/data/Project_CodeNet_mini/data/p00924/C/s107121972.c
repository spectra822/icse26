/*
  AOJ 1345
  Title:Bit String Reordering
  @kankichi573
*/
#include <stdio.h>
#include <string.h>

#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))
int M,N;
char b[15];
char b1[15];
int  p[15];
int  p1[15];

int solve(char bit[],int runlen[],int len,int runlenlen,char start)
{
  int pos;
  char *p;

  if(len==1)
    return(0);
  if(runlen[0]==0)
    return(solve(bit,runlen+1,len,runlenlen-1,start=='1'?'0':'1'));
  if(len==2)
    {
      if(bit[0]==start)
	return(0);
      else
	return(1);
    }
  else if(bit[0]==start)
    {
      runlen[0]--;
      return(solve(bit+1,runlen,len-1,runlenlen,start));
    }
  else if(start=='0')
    {
      p = strchr(bit,'0');
      pos =  p - bit;
      runlen[0]--;
      *p='1';
      return(pos+solve(bit+1,runlen,len-1,runlenlen,start));
    }
  else if(start=='1')
    {
      p = strchr(bit,'1');
      pos =  p - bit;
      runlen[0]--;
      *p='0';
      return(pos+solve(bit+1,runlen,len-1,runlenlen,start));
    }
}

main()
{
  int i,ret,c1,ce,ret1,ret2;
  
  scanf("%d %d ",&N,&M);

  for(i=c1=0;i<N;i++)
    {  
      scanf("%c ",&b[i]);
      if(b[i]=='1')
	c1++;
    }
  for(i=ce=0;i<M;i++)
    {
      scanf("%d",&p[i]);
      if((i & 1)==0)
	ce += p[i];
    }

    if(c1*2==N)
    {
      memcpy(b1,b,sizeof(b));
      memcpy(p1,p,sizeof(p));
      ret1=solve(b,p,N,M,'1');
      ret2=solve(b1,p1,N,M,'0');
      ret=min(ret1,ret2);
    }
  else if (ce==c1)
    ret=solve(b,p,N,M,'1');
  else
    ret=solve(b,p,N,M,'0');
  

  printf("%d\n",ret);
  
  return(0);
}