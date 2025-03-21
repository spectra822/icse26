#include<stdio.h>
#define min(p,q)((p)<(q)?(p):(q))

//自分より真に大きいのが7人以下
//取る点としては、nかn+1だけを考慮すればよい

int n;
int s[110],t[110];
int a[3][110],x[110];

void f(int*p){
	for(int i=0;i<n;i++){
		int cnt=0;
		for(int j=0;j<n;j++)if(p[j]>p[i])cnt++;
		t[i]=x[cnt];
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",x+i);
	for(int i=0;i<n;i++)scanf("%d%d%d",a[0]+i,a[1]+i,a[2]+i);
	int ans=1000;
	for(int k=0;k<3;k++){
		for(int i=0;i<n;i++)s[i]=0;
		for(int kk=0;kk<3;kk++)if(kk!=k){
			f(a[kk]);
			for(int i=0;i<n;i++)s[i]+=t[i];
		}

		int ori=a[k][0];
		for(int i=1;i<n;i++){
			for(int d=0;d<2;d++)if(a[k][i]+d>ori){
				a[k][0]=a[k][i]+d;
				f(a[k]);
				int cnt=0;
				for(int j=0;j<n;j++)if(s[j]+t[j]>s[0]+t[0])cnt++;
				if(cnt<=7)ans=min(ans,a[k][0]-ori);
			}
		}
		a[k][0]=ori;
	}
	if(ans==1000)puts("Saiko");
	else printf("%d\n",ans);
}
