var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n").map(Number);
Arr.forEach(function(v){
var t=v/9.8;
var y=4.9*t*t;
var n=Math.ceil((y+5)/5);
console.log(n);
});