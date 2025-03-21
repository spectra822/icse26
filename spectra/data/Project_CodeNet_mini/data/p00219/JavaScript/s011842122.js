var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n").map(Number);
while(true){
   var L=Arr.shift();
   if(L==0)break;
   var arr=[0,0,0,0,0,0,0,0,0,0];
   for(var i=0;i<L;i++){
      arr[Arr.shift()]++;
   }
   for(var i=0;i<10;i++){
      if(arr[i]==0)console.log("-");
      else console.log(Array(arr[i]+1).join("*"));
   }
}