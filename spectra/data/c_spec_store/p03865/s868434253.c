char buf[114514];
main(n){
	n=read(0,buf,114514);
	n--;
	puts(n+(buf[0]==buf[n-1])&1?"First":"Second");
}