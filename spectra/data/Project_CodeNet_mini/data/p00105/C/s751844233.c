#include <stdio.h>
#include <string.h>

#define MAX 100
#define PGMAX 1001
#define WDMAX 31

typedef struct _index {
	int pgnum[PGMAX];
	int tm;
	char str[WDMAX];
} index_t;

void swap( int i, int j, index_t idx[MAX] )
{
	char tmp_str[WDMAX];
	int tmp_pgnum[PGMAX];
	int tmp_tm;

	strcpy( tmp_str, idx[i].str );
	for ( int k = 0 ; k < PGMAX ; k++ ) {
		tmp_pgnum[k] = idx[i].pgnum[k];
	}
	tmp_tm = idx[i].tm;

	strcpy( idx[i].str, idx[j].str );
	for ( int k = 0 ; k < PGMAX ; k++ ) {
		idx[i].pgnum[k] = idx[j].pgnum[k];
	}
	idx[i].tm = idx[j].tm;

	strcpy( idx[j].str, tmp_str );
	for ( int k = 0 ; k < PGMAX ; k++ ) {
		idx[j].pgnum[k] = tmp_pgnum[k];
	}
	idx[j].tm = tmp_tm;
}

int main()
{
	index_t idx[MAX];
	char tmp_str[WDMAX] = {};
	int tmp_pgnum = 0, rgnum = 0, i = 0, j = 0, flag = 0, k = 0;

	while ( scanf( "%s %d", tmp_str, &tmp_pgnum ) != EOF ) {
		flag = 1;
		i = 0;
		while ( i < rgnum ) {
			if ( strcmp( tmp_str, idx[i].str ) == 0 ) {
				// BEPO?$5$l$?J8;zNs$NCf$+$i, B:#2sF~NO$5$l$?J8;zNs$,EPO?$5$l$F$$$k$+3NG'$9$k
				idx[i].pgnum[tmp_pgnum] = 1;
				idx[i].tm++;
				flag = 0; // BF~NOJ8;zNs$,EPO?:Q$_$N>l9g
				break;
			}
			i++;
		}

		if ( flag ) {
			// BF~NOJ8;zNs$,EPO?$5$l$F$$$J$$>l9g
			idx[rgnum].pgnum[tmp_pgnum] = 1;
			idx[rgnum].tm++;
			strcpy( idx[rgnum].str, tmp_str );
			rgnum++;
		}
		
	}

	// BF~NOJ8;zNs$N@0Ns$r9T$&
	for ( i = 0 ; i < rgnum ; i++ ) {
		for ( j = i+1 ; j < rgnum ; j++ ) {
			if ( strcmp( idx[i].str, idx[j].str ) > 0 ) {
				swap( i, j, idx );
			}
		}
	}

	// B@0Ns:Q$_$NF~NOJ8;zNs$NG[Ns$KBP$7$F, B=P8=$7$?%Z!<%8HV9f$J$I$r=PNO$9$k
	for ( i = 0 ; i < rgnum ; i++ ) {
		printf( "%s\n", idx[i].str );
		k = 0;
		for ( j = 0 ; j < PGMAX ; j++ ) {
			if ( idx[i].pgnum[j] == 1 ) { 
				if ( k == idx[i].tm-1 ) {
					printf( "%d\n", j );
					break;
				} else {
					printf( "%d ", j );
					k++;
				}
			}
		}
	}

	return 0;	
}

