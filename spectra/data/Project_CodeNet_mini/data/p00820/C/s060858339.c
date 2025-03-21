/*
  AOJ 1241
  Title:Lagrange's Four-Square Theorem
  @kankichi573
*/
#include <stdio.h>


int solve(int n,int c,int low)
{
  int i,ret;
  ret=0;
  for(i=low;i*i<=n;i++)
    {
      if(n==i*i)
	ret++;
      else if(c<4)
	ret+=solve(n-i*i,c+1,i);
    }
  return(ret);
}
main()
{
  int n,ret;
  while(scanf("%d",&n) && n)
    {
      ret=solve(n,1,1);
      printf("%d\n",ret);
    }
  return(0);
}