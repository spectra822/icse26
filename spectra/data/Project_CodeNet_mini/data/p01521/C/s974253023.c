#include<stdio.h>
#include<string.h>
char B[200],c[256];
int i;
int main()
{
	gets(B);
	for(;B[i];i++)
		if(!i||B[i]!=B[i-1])c[B[i]]++;
	i=!puts(c['o']<c['x']?"x":"o");
}