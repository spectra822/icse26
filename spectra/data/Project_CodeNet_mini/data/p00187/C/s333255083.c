#include<math.h>
L(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy,double*X,double*Y){
	int acx,acy,bunbo;
	int r,s;
	//printf("(%d,%d)-(%d,%d) , (%d,%d)-(%d,%d) : ",ax,ay,bx,by,cx,cy,dx,dy);
	acx=cx-ax;
	acy=cy-ay;
	bunbo=(bx-ax)*(dy-cy)-(by-ay)*(dx-cx);
	if(bunbo){
		r=((dy-cy)*acx-(dx-cx)*acy);
		s=((by-ay)*acx-(bx-ax)*acy);
		if(bunbo<0){
			r=-r;
			s=-s;
			bunbo=-bunbo;
		}
		if(r>=0&&r<=bunbo&&s>=0&&s<=bunbo){
			*X=ax+r/(double)bunbo*(bx-ax);
			*Y=ay+r/(double)bunbo*(by-ay);
			//printf("(%f,%f)\n",*X,*Y);
			return 1;
		}
	}
	//printf("NA\n");
	return 0;
}
main(){
	int x1[3],y1[3],x2[3],y2[3];
	double X[3],Y[3],S;
	int i=0;
	for(;~scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i);){
		if(++i==3){
			if(L(x1[0],y1[0],x2[0],y2[0],x1[1],y1[1],x2[1],y2[1],X+0,Y+0)&&
			   L(x1[1],y1[1],x2[1],y2[1],x1[2],y1[2],x2[2],y2[2],X+1,Y+1)&&
			   L(x1[2],y1[2],x2[2],y2[2],x1[0],y1[0],x2[0],y2[0],X+2,Y+2))
			{
				S=0;
				for(i=0;i<3;i++){
					S+=(X[i]-X[(i+1)%3])*(Y[i]+Y[(i+1)%3])/2;
				}
				S=fabs(S);
				if(S<1e-6)
					puts("kyo");
				else if(S<100000-1e-6)
					puts("syo-kichi");
				else if(S<1000000-1e-6)
					puts("kichi");
				else if(S<1900000-1e-6)
					puts("chu-kichi");
				else
					puts("dai-kichi");
			}else{
				puts("kyo");
			}
			i=0;
		}
	}
}