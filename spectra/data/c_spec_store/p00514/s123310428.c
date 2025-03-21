#include <stdio.h>

/* 20000! has 77338 digits */
/* 9 digits in one int */
#define TABAICHO_SIZE 8667
#define TABAICHO_BLOCK 1000000000
int tabaicho_main[TABAICHO_SIZE];

void tabaicho_set(int num) {
	int i;
	tabaicho_main[0]=num;
	for(i=1;i<TABAICHO_SIZE;i++)tabaicho_main[i]=0;
}

void tabaicho_mul(int num) {
	int kuriagari=0;
	long long calctemp;
	int i;
	for(i=0;i<TABAICHO_SIZE;i++) {
		calctemp=(long long)tabaicho_main[i]*num;
		calctemp+=kuriagari;
		tabaicho_main[i]=calctemp%TABAICHO_BLOCK;
		kuriagari=calctemp/TABAICHO_BLOCK;
	}
}

void tabaicho_div(int num) {
	long long remainder=0;
	int i;
	for(i=TABAICHO_SIZE-1;i>=0;i--) {
		remainder=remainder*TABAICHO_BLOCK+tabaicho_main[i];
		tabaicho_main[i]=remainder/num;
		remainder=remainder%num;
	}
}

void tabaicho_print(void) {
	int i;
	for(i=TABAICHO_SIZE-1;i>=0;i--) {
		if(tabaicho_main[i]>0)break;
	}
	printf("%d",tabaicho_main[i]);
	for(i--;i>=0;i--)printf("%09d",tabaicho_main[i]);
	putchar('\n');
}

int main(void) {
	int n,m,r;
	scanf("%d%d%d",&n,&m,&r);
	r-=n*m; /* n=3 r=8 m=1 xoo|xoo|xo */
	if(r<0)puts("0");
	else if(r==0)puts("1");
	else {
		int i,j,n2;
		/* n=3 r=5 oo|oo|o */
		/* (n+r-1)C(n-1) */
		tabaicho_set(1);
		n2=n-1;
		if((n+r-1)-(n-1)<n-1)n2=(n+r-1)-(n-1);
		for(i=0,j=n+r-1;i<n2;i++,j--)tabaicho_mul(j);
		for(i=1;i<=n2;i++)tabaicho_div(i);
		tabaicho_print();
	}
	return 0;
}