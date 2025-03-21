#include <stdio.h>

int rev(int n)
{
	int out;

//printf("(%d ", n);
	
	out = 0;
	
	while (n > 0){
		out = out * 10 + (n % 10);
		n /= 10;
	}

//printf("%d)", out);
	
	return (out);
}


int main(void)
{
	int n;
	int i;
	
	scanf("%d", &n);
	
	i = 0;
	
	while (1){
		if (n - i >= 0){
			if (rev(n - i) == n - i){
				printf("%d\n", n - i);
				break;
			}
		}
		if (rev(n + i) == n + i){
			printf("%d\n", n + i);
			break;
		}
		i++;
	}
	
	return (0);
}