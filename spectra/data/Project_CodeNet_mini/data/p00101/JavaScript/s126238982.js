var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var L=(Arr.shift())-0;
for(var i=0;i<L;i++){
var str=Arr[i];
console.log(str.replace(/Hoshino/g,"Hoshina"));
}