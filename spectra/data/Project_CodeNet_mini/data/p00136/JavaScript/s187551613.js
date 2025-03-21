var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n").map(Number);
var L=Arr.shift();
var arr=[[],[],[],[],[],[]];
for(var i=0;i<L;i++){
   if(185<=Arr[i])arr[5].push("*");
   else if(180<=Arr[i])arr[4].push("*");
   else if(175<=Arr[i])arr[3].push("*");
   else if(170<=Arr[i])arr[2].push("*");
   else if(165<=Arr[i])arr[1].push("*");
   else arr[0].push("*");
}

for(var i=0;i<arr.length;i++){
   console.log((i+1)+":"+arr[i].join(""));
}