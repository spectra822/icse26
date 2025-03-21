function bomb(){
   var obj={};
   var min=-1;
   var start=[];
   yx.forEach(function(v,i){
      v.forEach(function(value,j){
         if(value==2)start=[i,j];
      });
   });
   var ary=[[start,6,0]];
   while(true){
      if(ary.length==0)break;
      var v=ary.shift();
      var y=v[0][0];
      var x=v[0][1];
      var power=v[1];
      var cnt=v[2];
      if(obj.hasOwnProperty(y+","+x+","+power))continue;
      obj[y+","+x+","+power]=true; 
      if(yx[y][x]==3){
         min=cnt;
         break;
      }
      if(power==1)continue;
      var dy=[-1,0,0,1];
      var dx=[0,-1,1,0];
      for(var i=0;i<4;i++){
         var Y=y+dy[i];
         var X=x+dx[i];
         if(Y<0 || X<0 || Y>=h || X>=w || yx[Y][X]==0)continue;
         if(yx[Y][X]==1 || yx[Y][X]==3)ary.push([[Y,X],power-1,cnt+1]);
         else if(yx[Y][X]==4)ary.push([[Y,X],6,cnt+1]);
     }   
   }
   return min;
}
var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
while(true){
   var wh=arr.shift().split(" ").map(Number);
   if(wh.join(" ")=="0 0")break;
   var w=wh[0];
   var h=wh[1];
   var yx=[];
   for(var i=0;i<h;i++)yx.push(arr.shift().split(" ").map(Number));
   console.log(bomb());
}