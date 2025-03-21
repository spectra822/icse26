/*
A0647:set
 */
#include <stdio.h>
#include <stdlib.h>

int n,k,a[100001];

int comp( const void * a , const void * b ) {

  if( *( int * )a > *( int * )b ) {
    return 1;
  }
  else
  if( *( int * )a == *( int * )b ) {
    return 0;
  }
  return -1;
}


int main()
{
  int i,prev;
  int ret;
  scanf("%d",&n);

  for(i=0;i<n;i++)
    {
      scanf("%d",&a[i]);
    }
  qsort(a,n,sizeof(int),comp);
  prev=a[0];
  for(i=1,ret=1;i<n;i++)
  {
    if(a[i]!=prev)
      ret++;
    prev=a[i];
  }
  printf("%d\n",ret);
  return(0);
}

