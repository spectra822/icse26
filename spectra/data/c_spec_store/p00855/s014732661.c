i, t;
p( n )
{
	for ( i = t = 2; i * i <= n; ++i )
	{
		n%i?:t++;
	}
	return t - 2;
}
main( l, s, u )
{
	for ( ; scanf("%d", &l ), u = l; )
	{
		for( ; p(l); l-- );
		for( ; p(u); u++ );
		printf( "%d\n",  u - l );
	}
	return 0;
}