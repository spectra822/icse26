var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var n=input.trim()-0;
var i=0;
while(true){
   var a=(n-i)+"";
   var A=a.split("").reverse().join("");
   if(a==A)return console.log(a);
   var a=(n+i)+"";
   var A=a.split("").reverse().join("");
   if(a==A)return console.log(a);
   i++;
}