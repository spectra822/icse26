var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
while(true){
   var n=Arr.shift()-0;
   if(n==0)break;
   var a=0;
   var b=0;
   for(var i=0;i<n;i++){
      var arr=(Arr.shift()).split(" ").map(Number);
      if(arr[0]>arr[1])a+=arr[0]+arr[1];
      if(arr[0]<arr[1])b+=arr[0]+arr[1];
      if(arr[0]==arr[1]){a+=arr[0];b+=arr[1];}
   }
   console.log(a+" "+b);
}