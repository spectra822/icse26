var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var [n,m]=arr.shift().split(" ").map(Number);
var lane=[];
for(var i=0;i<n;i++)lane[i]=[];
arr.forEach(v=>{
   var [a,b]=v.split(" ").map(Number);
   if(a==0)console.log(lane[b-1].shift());
   else if(a==1){
      var m=lane.map(v=>v.length);
      var s=m.indexOf(Math.min(...m));
      lane[s].push(b);
   }
});

