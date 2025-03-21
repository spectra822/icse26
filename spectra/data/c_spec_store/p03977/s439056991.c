char buf[10000],out[20000];
char r[10];
sz;outsz;
main()
{
	read(0,buf,10000);
	while(buf[sz++]>='0');
	while(buf[sz]>='0')
	{
		int N=0,D=0;
		for(;;)
		{
			char k=buf[sz++];
			if(k<'0')break;
			N=N*10+k-'0';
		}
		for(;;)
		{
			char k=buf[sz++];
			if(k<'0')break;
			D=D*10+k-'0';
		}
		int ans=N&1?127*--N+D:127*N-D;
		int ri=10;
		do{
			r[--ri]=ans%10+'0';
		}while(ans/=10);
		while(ri<10)out[outsz++]=r[ri++];
		out[outsz++]='\n';
	}
	write(1,out,outsz);
}
