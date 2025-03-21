
#include <stdio.h>

int main(){

  int i=0, x[2], y[2], r[2], rplus, rminus,rdistance;

  while(i<2){
    scanf("%d%d%d", &x[i],&y[i],&r[i]);
    i++;
  }

  rdistance = (x[0]-x[1])*(x[0]-x[1]) +	(y[0]-y[1])*(y[0]-y[1]); //２乗すればsqrtが不要               
  rplus = (r[0]+r[1])*(r[0]+r[1]);
  rminus = (r[0]-r[1])*(r[0]-r[1]); //２乗して、|r1-r2|の絶対値を必要なくしている.他も２乗する.       

  if(rdistance > rplus)	printf("4\n");
  else if(rdistance == rplus) printf("3\n");
  else if(rminus < rdistance &&	rdistance < rplus) printf("2\n");
  else if(rdistance == rminus) printf("1\n");
  else if(rdistance < rminus) printf("0\n");



  return 0;
}


