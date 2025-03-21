#include <stdio.h>
#include <stdlib.h>

int main(void){
  int c[3][3];
  int i, j;

  int min[3];

  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      scanf("%d", &c[i][j]);
    }
    if(c[i][0]>c[i][1]){
      if(c[i][1]>c[i][2]) min[i] = c[i][2];
      else min[i] = c[i][1];
    } else {
      if(c[i][0]>c[i][2]) min[i] = c[i][2];
      else min[i] = c[i][0];
    }
  }



  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      c[i][j] -= min[i];
    }
  }

  for(j=0; j<3; j++){
    if(c[0][j]!=c[1][j] || c[0][j]!=c[2][j]){
      printf("No\n");
      exit(0);
    }
  }

  printf("Yes\n");

  return (0);
}
