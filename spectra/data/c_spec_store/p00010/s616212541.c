#include <stdio.h>

int main(){
	int i, n;
	
		scanf("%d", &n);
		
		for(i = 0; i < n; i++){
			double x1, y1, x2, y2, x3, y3, px, py, x, s, r, a1 ,a2, b1, b2, c1, c2;
			
			scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
			a1 = 2 * (x2 - x1);
			b1 = 2 * (y2 - y1);
			c1 = x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2;
		
			a2 = 2 * (x3 - x1);
			b2 = 2 * (y3 - y1);
			c2 = x1 * x1 - x3 * x3 + y1 * y1 - y3 * y3;
		
			px = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
			py = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);
			
			x = 0.0;
			s = (x1 - px) * (x1 - px) + (y1 - py) * (y1 - py);
			r = s / 2.0;
			
			while(r != x){
				x = r;
				r = (r + s / r) / 2.0;
			}
			
			if(r < 0) r *= -1;
		
			printf("%.3lf %.3lf %.3lf\n", px, py, r);
		}
	
	return 0;
}