#include <stdio.h>

#define MAX 50001

int makePrimeTable( int * table )
{
        int i, j;
        for ( i = 0 ; i < MAX ; i++ ) {
                table[i] = 0;
        }

        for ( i = 2 ; i < MAX ; i++ ) {
                if ( table[i] == 0 ) {
                        for ( j = 2 ; i * j < MAX ; j++ ) {
                                table[i*j] = 1;
                        }
                }
        }
        return 0;
}


int main()
{
        int n, i, j, cnt;
        int ptable[MAX];
        makePrimeTable( ptable );
        while ( scanf( "%d", &n ) == 1 ) {
                cnt = 0;
                if ( n == 0 ) {
                        break;
                } else {
                        for ( i = 2 ; i <= n / 2 ; i++ ) {
                                if ( ptable[i] == 0 && ptable[n-i] == 0 ) {
                                        cnt++;
                                }
                        }
                        printf( "%d\n", cnt );
                }
        }
        return 0;
}

