n,i,a[100009];main(){
	scanf("%d",&n);for(i=0;i<n;i++)scanf("%d",&a[i]);
	for(i=n-1;i>=1;i--){
    	if(a[i]<a[i-1])a[i-1]--;
    	if(a[i]<a[i-1]){printf("No");return 0;}
	}
	printf("Yes");
}