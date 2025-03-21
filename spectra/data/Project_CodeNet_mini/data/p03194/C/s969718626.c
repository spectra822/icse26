long n,p,ans=1;
main()
{
	scanf("%ld%ld",&n,&p);
	for(long i=2;i*i<=p;i++)
	{
		long cnt=0;
		while(p%i<1)cnt++,p/=i;
		if(cnt>=n)
		{
			for(int j=0;j<cnt/n;j++)ans*=i;
		}
	}
	if(p>1&&n==1)ans*=p;
	printf("%ld\n",ans);
}