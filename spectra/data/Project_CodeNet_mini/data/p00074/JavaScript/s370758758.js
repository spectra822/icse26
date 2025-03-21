function hms(x){
   var S=x%60;
   var M=(x%3600-S)/60;
   var H=(x-(M*60)-S)/3600;
   if(S<10)S="0"+S;
   if(M<10)M="0"+M;
   if(H<10)H="0"+H;
   return [H,M,S].join(":");
}

var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
for(var i=0;i<Arr.length;i++){
   var arr=Arr[i].split(" ").map(Number);
   var h=arr[0];
   var m=arr[1];
   var s=arr[2];
   if(h==-1 && m==-1 && s==-1)break;
   var time=(7200)-(h*3600)-(m*60)-s;
   console.log(hms(time));
   console.log(hms(time*3));
}