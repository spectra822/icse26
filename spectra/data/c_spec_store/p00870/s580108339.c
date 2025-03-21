/*
  AOJ 1291
  Title:Search of Concatenated Strings
  @kankichi573
*/
#include <stdio.h>
#include <string.h>

int n,m;
char e[12][21];
int  len[12];
char t[5001];
char flag[5001][4096];
void dump_flag(char flag[5001][4096],int len)
{
  int i,j;
  for(i=0;i<len;i++)
    for(j=0;j<4096;j++)
      if(flag[i][j])
	printf("%d %d\n",i,j);
}
main()
{
  int l,ln,l_s,i,j,k,cnt,loop,mask,pat;
  char buf[101];
  while(scanf("%d %d",&n,&m) && (n||m))
    {
      memset(flag,0,sizeof(flag));
      for(i=0;i<n;i++)
	{
	  scanf("%s",&e[i][0]); 
	  len[i]=strlen(&e[i][0]);
	}
      t[0]='\0';
      for(i=0;i<m;i++)
	{
	  scanf("%s",buf);
	  ln=strlen(buf);
	  if(buf[ln-1]<' ')
	    buf[ln-1]='\0';
	  strcat(t,buf);
	}
      l_s=strlen(t);
      loop=1<<n;
      for(i=0,cnt=0;i<l_s;i++)
	{
	  for(j=0;j<loop;j++)
	    {
	    if(j && flag[i][j]==0)
	    continue;
	    for(k=0,mask=1;k<n;k++,mask<<=1)
		{
		  if(j & mask)
		    continue;
		  if(0==strncmp(&e[k][0],&t[i],(l=len[k])))
		    {
		      pat=j|mask;
		      flag[i+l][pat]=1;
		    }
		}
	    }
	}
      for(i=0,cnt=0;i<=l_s;i++)
	cnt += flag[i][loop-1];
      printf("%d\n",cnt);
    }
  return(0);
}