#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
const double EPS=1e-10;
typedef struct P{double x,y;int o,l;}P;
int C,N,XS,YS,XT,YT,O,L,XA,YA,XB,YB,i,b,tx,ty,c,T,R;
double r,s;
P ST[105];
int cmp(const void* a,const void* b)
{
	P* A=(P*)a;
	P* B=(P*)b;
	if(abs(A->x-B->x)<0)
	{
		if(A->y-B->y<0)return -1;
		if(B->y>A->y<0)return 1;
	}
	if(A->x-B->x<0)return -1;
	if(B->x-A->x<0)return 1;
	return 0;
}

int main()
{
	for(scanf("%d",&C);C--;)
	{
		memset(ST,0,sizeof(ST));
		scanf("%d%d%d%d%d",&XA,&YA,&XB,&YB,&N);
		for(i=c=0;i<N;i++)
		{
			scanf("%d%d%d%d%d%d",&XS,&YS,&XT,&YT,&O,&L);
			tx=XS-XA;
			ty=YS-YA;
			b=(XB-XA)*(YT-YS)-(YB-YA)*(XT-XS);
			if(b==0)continue;
			r=(double)((YT-YS)*tx-(XT-XS)*ty)/b;
			s=(double)((YB-YA)*tx-(XB-XA)*ty)/b;
			if(r<EPS||s<EPS||1.0-r<EPS||1.0-s<EPS)continue;
			if(r>EPS&&1.0-r>EPS){P ins={XA+r*(XB-XA),YA+r*(YB-YA),O,L};ST[c++]=ins;}
			else{P ins={XS+s*(XT-XS),YS+s*(YT-YS),O,L};ST[c++]=ins;}
		}
		qsort(ST,c,sizeof(P),cmp);
		R=999;
		for(L=0;L<2;L++)
		{
			for(T=L,i=b=0;i<c;i++)
			{
				if(ST[i].o==1&&ST[i].l!=T){b++;T^=1;}
				if(ST[i].o!=1&&ST[i].l==T){b++;T^=1;}
			}
			R=R<b?R:b;
		}
		printf("%d\n",R);
	}
	return 0;
}