var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var str=input.trim();
if(str=="1 0 0")console.log("Close");
if(str=="0 1 0")console.log("Close");
if(str=="1 1 0")console.log("Open");
if(str=="0 0 1")console.log("Open");
if(str=="0 0 0")console.log("Close");