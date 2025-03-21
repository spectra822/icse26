#include<stdio.h>
int main(){
  char s[50];
  int d[5],n,c,i,r;
  int m12=365*13+4-11;
  int d400=365*400+100-4+1;
  int d100=365*100+25 -1;
  int d4  =365*4  +1;
  int a[5];
  int M[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  unsigned long long dt,t;
  while(scanf("%s",s),s[0]-'#'){
    for(i=c=n=r=0;s[i];i++){
      if(s[i]=='.'){
	c++;
	d[r++]=n;
	n=0;
      }
      else{
	n*=10;
	n+=s[i]-'0';
      }
    }
    d[r]=n;
    dt=0;//-m12;
    if(c==2){
      //printf("%d %d %d\n",d[0],d[1],d[2]);
      for(i=1;i<d[1];i++)dt+=M[i];
      if(d[1]>2&&d[0]%4==0&&(d[0]%100||d[0]%400==0))dt++;
      dt+=(unsigned long long)d[2]-1;
      d[0]-=2001;
      dt+=(unsigned long long)365*d[0]+d[0]/4-d[0]/100+d[0]/400+366-m12;
      //printf("%d\n",m12);
      a[4]=dt%20;
      dt/=20;
      a[3]=dt%18;
      dt/=18;
      a[2]=dt%20;
      dt/=20;
      a[1]=dt%20;
      dt/=20;
      a[0]=dt%13;
      printf("%d.%d.%d.%d.%d\n",a[0],a[1],a[2],a[3],a[4]);      
    }
    else{
      dt=d[0];
      dt=dt*20+d[1];
      dt=dt*20+d[2];
      dt=dt*18+d[3];
      dt=dt*20+d[4];
      dt+=4738+1;
      for(a[0]=2000;dt>365;a[0]++){
	t=dt;
	dt-=365;
	if(a[0]%4==0&&(a[0]%100||a[0]%400==0))dt--;
      }
      if(dt==0){
	dt=t;
	a[0]--;
      }
      /*a[0] =(dt/d400)*400;
      dt%d400;
      a[0]+=(dt/d100)*100;
      dt%=d100;
      a[0]+=(dt/d4  )*4  ;
      dt%=d4  ;
      a[0]+=(dt/365);
      dt%=365;//*/
      //if(59>dt&&a[0]%4==0&&(a[0]%100||a[0]%400==0))dt++;
      for(i=1;i<13;i++){
	if(dt<=M[i])break;
	dt-=M[i];
	if(i==2&&a[0]%4==0&&(a[0]%100||a[0]%400==0)){
	  dt--;
	  if(dt==0){
	    dt=29;
	    break;
	  }
	}
      }
      printf("%d.%d.%lld\n",a[0],i,dt);
    }
  }
  return 0;
}