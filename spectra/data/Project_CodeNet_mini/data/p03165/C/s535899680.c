# include <string.h>
# include <stdlib.h>
# include <stdio.h>
int max (int a,int b){
	if(a>=b) return a;
	else return b;
}
int main(){
	char *s1,*s2;
	s1=(char*)malloc(3000*sizeof(char));
	s2=(char*)malloc(3000*sizeof(char));
	scanf ("%s %s",s1,s2);
	int **arr,i,j;
	int l_s1=strlen(s1);
	int l_s2=strlen(s2);
	arr=(int**)malloc((l_s1+1)*sizeof(int*));
	for(i=0;i<=l_s1;i++) arr[i]=(int*)malloc((l_s2+1)*sizeof(int));
	for(i=0;i<l_s2+1;i++) arr[0][i]=0;
	for(i=0;i<l_s1+1;i++) arr[i][0]=0;
	for(i=1;i<l_s1+1;i++){
		for(j=1;j<l_s2+1;j++){
			if(s1[i-1]==s2[j-1]) arr[i][j]=arr[i-1][j-1]+1;
			else arr[i][j]=max(arr[i-1][j],arr[i][j-1]);
		}
	}
	int len=arr[l_s1][l_s2];
	char *ans;
	ans=(char*)malloc(len*sizeof(char));
	int ind=len-1;
	int r=l_s1,c=l_s2;
	while (r>=1 && c>=1){
		if(s1[r-1]==s2[c-1]) {
			ans[ind]=s1[r-1];
			r-=1;
			c-=1;
			ind-=1;
		}
		else if (arr[r][c]==arr[r-1][c]){
			r-=1;
			continue;
		}
		else{
			c-=1;
			continue;
		}
	}
	for(i=0;i<arr[l_s1][l_s2];i++)printf ("%c",ans[i]);
	return 0;
}