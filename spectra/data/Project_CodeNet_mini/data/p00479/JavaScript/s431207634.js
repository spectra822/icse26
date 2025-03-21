var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var N=arr.shift()-0;
var k=arr.shift()-0;
while(k--){
   var ary=arr.shift().split(" ").map(Number);
   var a=ary[0];
   var b=ary[1];
   a=Math.min(a,N-a+1);
   b=Math.min(b,N-b+1);
   var max=Math.min(a,b);
   console.log((max-1)%3+1);
}