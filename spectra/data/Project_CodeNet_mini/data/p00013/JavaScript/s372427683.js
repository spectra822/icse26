var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n").map(Number);
var arr=[];
Arr.forEach(function(v){
if(v==0){console.log(arr.pop());}
else{arr.push(v);}
});