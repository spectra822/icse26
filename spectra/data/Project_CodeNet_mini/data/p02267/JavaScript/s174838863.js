var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var a=Arr[1].split(" ").map(Number);
var b=Arr[3].split(" ").map(Number);
var cnt=0;
var len=a.length;

for(var i=0;i<b.length;i++){
   if(linearSearch(b[i]))cnt++;
}
console.log(cnt);
 
function linearSearch(key){
   var i=0;
   a[len]=key;
   while(a[i]!=key){
      i++;
      if(i>=len)return false;
   }
   return true;
}