var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var obj={};
for(var i=0;i<Arr.length;i++){
   var arr=Arr[i].split(" ");
   var a=arr[0];
   var b=arr[1];
   if(a in obj){obj[a]+=(" "+b);}
   else{obj[a]=b;}
}
var keys=[];
for(var k in obj){
   keys.push(k);
   obj[k]=obj[k].split(" ").map(Number).sort(function(a,b){return a-b;}).join(" ");
}
keys.sort();
for(var i=0;i<keys.length;i++){
   console.log(keys[i]+"\n"+obj[keys[i]]);
}