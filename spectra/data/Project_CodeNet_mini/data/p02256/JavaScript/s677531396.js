 var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.split(" ").map(Number);
var a=arr[0];
var b=arr[1];
if(a===b){
console.log(a);
return;
}
var x=Math.max(a,b);
var y=Math.min(a,b);
var c=x%y;
for(var i=c;i>=1;i--){
if(x%i==0 && y%i==0)break;
}
console.log(i);