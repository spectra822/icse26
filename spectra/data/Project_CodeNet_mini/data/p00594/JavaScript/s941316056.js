var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
while(true){
   var n=arr.shift()-0;
   if(n===0)break;
   var ary=arr.shift().split(" ").map(Number);
   var obj={};
   ary.forEach(function(v){
      if(obj.hasOwnProperty(v)==false)obj[v]=1;
      else obj[v]++;
   });
   var ans="NO COLOR";
   for(var k in obj){
      if(obj[k]>n/2)ans=k;
   }
   console.log(ans);
}