var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
for(var I=0;I<Arr.length;I++){
   var nx=Arr[I].split(" ").map(Number);
   var n=nx[0];
   var x=nx[1];
   if(n==0 && x==0)break;
   var cnt=0;
   for(var i=1;i<=n;i++){
      for(var j=i+1;j<=n;j++){
         if(i+j>=x)break;
         var k=x-(i+j);
         if(k>j && k<=n)cnt++;
      }
   }
   console.log(cnt);
}