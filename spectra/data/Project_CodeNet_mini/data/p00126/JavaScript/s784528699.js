function NotOne(arr){
   var cnt=[0,0,0,0,0,0,0,0,0,0];
   arr.forEach(function(v){cnt[(v-0)]++;});
   var bad=[];
   cnt.forEach(function(v,i){if(v>=2)bad.push(i);});
   var result=[];
   arr.forEach(function(v,i){if(bad.indexOf(v)!=-1)result.push(i);});
   return result;
}
var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=input.trim().split("\n");
var STR="";
var n=Arr.shift()-0;
for(var I=0;I<n;I++){
   var yx=[];
   var YX=[];
   for(var i=0;i<9;i++){
      var v=Arr.shift().split(" ").map(Number);
      yx.push(v);
      YX.push([0,0,0,0,0,0,0,0,0]);
   }
   for(var i=0;i<9;i++){
      var re=NotOne(yx[i]);
      re.forEach(function(v){YX[i][v]++;});
   }
   for(var i=0;i<9;i++){
      var yy=[];
      for(var j=0;j<9;j++)yy.push(yx[j][i]);
      var re=NotOne(yy);
      re.forEach(function(v){YX[v][i]++;});
   }
   for(var y=0;y<3;y++){
      for(var x=0;x<3;x++){
         var i=y*3;
         var j=x*3;
         var z=[
         [0+i,0+j],[0+i,1+j],[0+i,2+j],
         [1+i,0+j],[1+i,1+j],[1+i,2+j],
         [2+i,0+j],[2+i,1+j],[2+i,2+j]
         ];
         var zz=[];
         z.forEach(function(v){zz.push(yx[v[0]][v[1]]);});
         var re=NotOne(zz);
         re.forEach(function(v){YX[z[v][0]][z[v][1]]++;});
      }
   }
   yx.forEach(function(V,i){
      V.forEach(function(v,j){
         yx[i][j]=(YX[i][j]>=1)?"*"+v:" "+v;
      });
   });
   STR+=yx.join("\n").replace(/\,/g,"")+"\n\n";
}
console.log(STR.trim());