var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var str=input.trim();
str=str.replace(/o+/g,0);
str=str.replace(/x+/g,1);
var a=str[0];
var b=str[str.length-1];
var ans="x";
if(a==0 && b==1)ans="o";
if(a==0 && b==0)ans="o";
if(a==1 && b==0)ans="o";
console.log(ans);