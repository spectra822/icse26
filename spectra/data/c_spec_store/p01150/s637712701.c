/*
  AOJ 2025
  Title:Eight Princes
  @kankichi573
*/
#include <stdio.h>
#include <string.h>
#define FACT8 40320
#define N_OF_PRINCES 8

int N;
int result[70];

void dump(int f)
{
#ifdef DEBUG
  int i;
  if(f==0)
    {
      for(i=0;i<N;i++)
	printf("%d|",result[i]);
      printf("\n");
    }
  else if(f==1)
    {
      for(i=0;i<N-1;i++)
	printf("%d|",result[i]);
      printf("1:\n");
    }
  else if (f==2)
    {
      for(i=0;i<N/2-1;i++)
	printf("%d|",result[i]);
      printf("1:");
      for(i=N/2;i<N-1;i++)
	printf("%d|",result[i]);
      printf("0:\n");
      for(i=0;i<N/2-1;i++)
	printf("%d|",result[i]);
      printf("0:");
      for(i=N/2;i<N-1;i++)
	printf("%d|",result[i]);
      printf("1+\n");
    }
  else if(f==3)
    {
      for(i=0;i<N/2-1;i++)
	printf("%d|",result[i]);
      printf("0:");
      for(i=N/2;i<N-1;i++)
	printf("%d|",result[i]);
      printf("1;\n");
    }
  else if(f==4)
    {
      for(i=0;i<N/2-1;i++)
	printf("%d|",result[i]);
      printf("1:");
      for(i=N/2;i<N-1;i++)
	printf("%d|",result[i]);
      printf("0@\n");
    }
#endif
}

unsigned int memo[70][9][3][3];

unsigned int calc_odd_1(int pos,int princes,int sitdown,int zero_sitdown)
{
  unsigned int ret;

  if(ret=memo[pos][princes][sitdown][zero_sitdown])
    return(ret);

  if(princes==0)
    {
      dump(0);
      ret=1;
    }
  else if(pos==N-1 && princes>1)
    ret=0;
  else if(pos==N-1 && princes==1)
    if(zero_sitdown==0 && sitdown==0)
      {
	dump(1);
	ret=1;
      }
    else
      ret=0;
  else
    {
      if(sitdown==0)
	{
	  result[pos]=1;
	  ret=calc_odd_1(pos+1,princes-1,1,zero_sitdown);
	}
      else
	ret=0;
      
      result[pos]=0;
      ret+=calc_odd_1(pos+1,princes,0,zero_sitdown);
    }
  memo[pos][princes][sitdown][zero_sitdown]=ret;
  return(ret);
}

unsigned int calc_odd(int N)
{
  unsigned int ret=0;
  
  result[0]=1;
  ret+=calc_odd_1(1,N_OF_PRINCES-1,1,1);
  result[0]=0;
  ret+=calc_odd_1(1,N_OF_PRINCES,0,0);
  return(ret);
}

unsigned int calc_even_1(int pos,int princes,int sitdown,int zero_sitdown)
{
  unsigned int ret;

  //printf("Pos=%d pr=%d\n",pos,princes);
  if(ret=memo[pos][princes][sitdown][zero_sitdown])
    return(ret);

  if(princes==0)
    {
      dump(0);
      ret=1;
    }
  else if(pos==N/2-1 && princes>1)
    ret=0;
  else if(pos==N/2-1 && princes==1)
    {
      if(zero_sitdown==0 && sitdown==0)
	{
	  dump(2);
	  ret=2;
	}
      else if((zero_sitdown==2||zero_sitdown==0) && (sitdown==1 || sitdown==0))
	{
	  dump(3);
	  ret=1;
	}
      else if((zero_sitdown==1||zero_sitdown==0) && (sitdown==2 || sitdown==0))
	{
	  dump(4);
	  ret=1;
	}
      else
	ret=0;
    }
  else
    {
      ret=0;
      if(sitdown==0 || sitdown==2)
	{
	  result[pos]=1;result[pos+N/2]=0;
	  ret +=calc_even_1(pos+1,princes-1,1,zero_sitdown);
	}
      if(sitdown==0 || sitdown==1)
	{
	  result[pos]=0;result[pos+N/2]=1;
	  ret +=calc_even_1(pos+1,princes-1,2,zero_sitdown);
	}

      result[pos]=0;result[pos+N/2]=0;
      ret+=calc_even_1(pos+1,princes,0,zero_sitdown);
    }
  memo[pos][princes][sitdown][zero_sitdown]=ret;
  return(ret);
}

unsigned int calc_even(int N)
{
  unsigned int ret=0;
  
  result[0]=1;result[N/2]=0;
  ret+=calc_even_1(1,N_OF_PRINCES-1,1,1); //zenhan
  result[0]=0;result[N/2]=1;
  ret+=calc_even_1(1,N_OF_PRINCES-1,2,2); //kouhan
  result[0]=  result[N/2]=0;
  ret+=calc_even_1(1,N_OF_PRINCES  ,0,0); //none
  return(ret);
}


main()
{
  long long ret;

  while(scanf("%d",&N) && N)
    {
      memset(memo,0,sizeof(memo));
      if(N<=16)
	ret=0;
      else if(N & 1)
	ret=(long long)FACT8*calc_odd(N);
      else
	ret=(long long)FACT8*calc_even(N);
      printf("%lld\n",ret);
    }
  return(0);
}