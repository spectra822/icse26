var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr = input.trim().split("\n").map(Number);
var a = arr[0];
var b = arr[1];
var c = arr[2];
var d = arr[3];
var e = arr[4];
var t = 0;
if (a < 0) {
   t += Math.abs(a) * c + d;
   a = 0;
}
t += (b - a) * e;
console.log(t);