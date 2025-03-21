function bomb(y,x){
   var PM=(y%2==1)?0:1;
   var dy=[[-1,-1,0,0,1,1],[-1,-1,0,0,1,1]];
   var dx=[[0,1,-1,1,0,1],[-1,0,-1,1,-1,0]];
   for(var i=0;i<6;i++){
      var Y=y+dy[PM][i];
      var X=x+dx[PM][i];
      if(Y<0 || X<0 || Y>=h+2 || X>=w+2)continue;
      if(yx[Y][X]==1)cnt++;
      if(yx[Y][X]==0){
         yx[Y][X]=2;
         bomb(Y,X);
      }
   }
}
var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var wh=arr.shift().split(" ").map(Number);
var w=wh[0];
var h=wh[1];
var yx=[];
var zero=[];
for(var i=0;i<w+2;i++)zero.push(0);
yx.push(zero.slice());
for(var i=0;i<h;i++)yx.push(("0 "+arr.shift()+" 0").split(" ").map(Number));
yx.push(zero.slice());
var cnt=0;
yx[0][0]=2;
bomb(0,0);
console.log(cnt);