#include<stdio.h>

int bs (int [], int, int);

int main(void)
{
  int i,j,n,a[100000],dp[100000];

  scanf("%d",&n);
  for(i=0;i<=n-1;i++)
    {
      scanf("%d",&a[i]);
    }
  dp[0]=-1;
  dp[1]=a[0];
  j=1;
  for(i=1;i<=n-1;i++)
    {
      if(dp[j]<a[i])
	{
	  dp[j+1]=a[i];
	  j++;
	}
      else
	{
	  dp[bs(dp,j+1,a[i])]=a[i];
	}
    }
  printf("%d\n",j);
  return 0;
}

int bs (int D[], int n, int c) 
{
    int j,k,l;
    j=0;
    k=n-1;
    while(1)
    {
        if(j<=k)
        {
            l=(j+k)/2;
            if(D[l] > c)
            {
                k=l-1;
            }
            else if(D[l] < c)
            {
                j=l+1;
            }
            else
            {
                return l;
            }
        }
        else
        {
	  return k+1;
        }
    }
}