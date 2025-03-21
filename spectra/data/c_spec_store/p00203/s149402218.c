#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void listen(char str[],int size);
void listenSize(int *X,int *Y);
void listenCourse(int **course,int X,int Y);
void analyzeCourse(int **course,int X,int Y);

int SkiResort();

int main()
{
	while(SkiResort());
	return 0;
}

int SkiResort()
{
	int X,Y;
	listenSize(&X,&Y);
	if(X==0 && Y==0)
	{
		return 0;
	}
	int course[X][Y];
	int *pCourse[X];
	int i;
	for(i=0;i<X;i++)
	{
		pCourse[i]=course[i];
	}
	listenCourse(pCourse,X,Y);
	analyzeCourse(pCourse,X,Y);
	
	return 1;
}

void listen(char str[],int size)
{
	for(;1;)
	{
		fgets(str,size,stdin);
		if(strcmp(str,"\n")!=0)
		{
			break;
		}
	}
}

void listenSize(int *X,int *Y)
{
	char str[64];
	listen(str,sizeof(str));
	
	*X=atoi(strtok(str," "));
	*Y=atoi(strtok(NULL," "));
}
	

void listenCourse(int **course,int X,int Y)
{
	char str[1024];
	int i,j;
	for(j=0;j<Y;j++)
	{
		listen(str,sizeof(str));
		course[0][j]=atoi(strtok(str," "));
		for(i=1;i<X;i++)
		{
			course[i][j]=atoi(strtok(NULL," "));
		}
	}
}

void analyzeCourse(int **course,int X,int Y)
{
	int i,j,k,m;
	int pattern[X][Y+2];
	for(i=0;i<X;i++)
	{
		for(j=0;j<Y+2;j++)
		{
			pattern[i][j]=0;
		}
	}
	
	for(i=0;i<X;i++)
	{
		if(course[i][0]==0)
		{
			pattern[i][0]=1;
		}
	}
	for(j=0;j<Y-1;j++)
	{
		for(i=0;i<X;i++)
		{
			for(k=i-1;k<=i+1;k++)
			{
				if(k<0 || X<=k)
				{
					continue;
				}
				switch(course[k][j+1])
				{
				  case 0:
					pattern[k][j+1]+=pattern[i][j];
					break;
				  case 1:
					pattern[k][j+1]=0;
					break;
				  default:
					if(k==i)
					{
						m=0;
						while(j+3+m<Y)
						{
							if(course[k][j+3+m]==2)
							{
								m+=2;
							}
							else
							{
								break;
							}
						}
						pattern[k][j+3+m]+=pattern[i][j];
					}
				}
			}
		}
	}
	int sum=0;
	for(i=0;i<X;i++)
	{
		for(k=Y-1;k<=Y+1;k++)
		{
			sum+=pattern[i][k];
		}
	}
	printf("%d\n",sum);
}