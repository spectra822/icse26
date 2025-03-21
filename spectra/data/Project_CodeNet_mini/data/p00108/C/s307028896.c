#include <stdio.h>

#define MAX 13

int main()
{
	int n = 0, i = 0, flag = 0, cnt = 0;
	int numline[MAX] = {};
	int tmpline[MAX] = {};
	int num[101] = {};

	while ( scanf( "%d", &n ) == 1 ) {
		if ( n == 0 ) { break; }
		for ( i = 0 ; i < n ; i++ ) {
			scanf( "%d", &numline[i] );
		}
		flag = 1;
		cnt = 0;
		while ( flag ) {
			// B=P8=J8;zNs$N=i4|2=$r9T$&
			for ( i = 0 ; i < 101 ; i++ ) {
				num[i] = 0;
			}

			// B=P8=J8;zNs$N%+%&%s%H
			for ( i = 0 ; i < n ; i++ ) {
				num[numline[i]]++;
			}

			// B=P8=IQEYJ8;zNs$N:n@.
			for ( i = 0 ; i < n ; i++ ) {
				tmpline[i] = num[numline[i]];
			}

			cnt++; flag = 0;
			// numlineB$HtmplineB$NF1$8?tCM?t$r%+%&%s%H
			// BJ8;zNsD9$H0lCW$9$k>l9g$O, BFs$D$,F1$8G[Ns$G$"$k$3$H$r<($9
			for ( i = 0 ; i < n ; i++ ) {
				if ( tmpline[i] == numline[i] ) {
					flag++;
				}
			}

			if ( flag == n ) {
				/*for ( i = 0 ; i < n ; i++ ) {
					printf( "%3d %3d\n", numline[i], tmpline[i] );
				}*/
				flag = 0;
			} else { 
				// B0c$&J8;zNs$N>l9g$O!"<!$NA`:n$KHw$($F?tNs$N%3%T!<$r9T$&
				for ( i = 0 ; i < n ; i++ ) {
					numline[i] = tmpline[i];
				} 
				flag = 1;
			}
		}

		printf( "%d\n", cnt-1 );
		for ( i = 0 ; i < n ; i++ ) {
			if ( i == n-1 ) { 
				printf( "%d\n", tmpline[i] );
			} else { 
				printf( "%d ", tmpline[i] );
			}
		}
	}
	return 0;
}

