 #include<stdio.h>
 int main()
 {
     char S[3];
     int i,m=0;
 
     scanf("%s",S);
 
     for(i=0;i<3;i++){
       if(S[i]=='o') m++;
     }
 
     printf("%d\n",700+(100*m));
 
     return 0;
 }