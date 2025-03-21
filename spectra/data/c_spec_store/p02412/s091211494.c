#include <stdio.h> 

int main() {
  int n,x;
  int b,i,j,k,a;

  while(1) {
    scanf("%d %d",&n,&x);   
    b = 0;
    if( n == 0 && x == 0){
      break;
    }
    for(k = 1; k <= n ; k++) {


      for(j = 1; j <= n ; j++) {

	for(i = 1; i <= n; i++) {
	  
	  if(i == j || j == k || i ==k) {
	    
	  }else{
	    a = i + j + k;
	    if(a == x) {
	     
	      b += 1;
 
	    }
	  }
	  
	}//i
	
      }//j

    }//k
    printf("%d\n",b/6);
  }


  return 0;
}
