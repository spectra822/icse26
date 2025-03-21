#include<stdio.h>
int main( )
{
    int n , num[1000] , count = 0  , i ;
    scanf("%d" , &n);
    
    for( i = 1 ; i <= n ; i++)
        scanf("%d" , &num[i]);
    
    for( i = 1 ; i < n-1 ; i++)
    {
        if( num[i] < num[i+1])
        {
            if( num[i+1] < num[i+2])
                count++ ;
        }
        
        else if( num[i] > num[i+1] )
        {
                if( num[i+1] > num[i+2])    
                    count++ ;
        }
    }
    
    printf("%d\n" , count);
    
    return 0 ;
}
