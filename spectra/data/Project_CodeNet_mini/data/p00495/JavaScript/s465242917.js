var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var ab=arr.shift().split(" ").map(Number);
var a=ab[0];
var b=ab[1];
if(b== undefined)b=arr.shift()-0;
var A=arr.shift().split(" ").map(Number);
var B=arr.shift().split(" ").map(Number);
var max=0;
for(var i=0;i<b;i++){
   var j=0;
   var k=i;
   var cnt=0;
   while(true){
      if(a<=j || b<=k)break;
      if(B[k]==A[j]){k++;cnt++;}
      j++;
   }
   max=Math.max(max,cnt);
}
console.log(max);