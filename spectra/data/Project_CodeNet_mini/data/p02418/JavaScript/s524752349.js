var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var a=Arr[0]+Arr[0]+Arr[0];
var b=Arr[1];
console.log((a.indexOf(b)!==-1)?"Yes":"No");