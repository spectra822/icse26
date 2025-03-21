var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var n=Arr.shift()-0;
while(n>0){
   var a=(Arr.shift()).split("").reverse().map(Number);
   var b=(Arr.shift()).split("").reverse().map(Number);
   var c=[];
   var max=Math.max(a.length,b.length);
   for(var i=0;i<max+1;i++)c[i]=0;
   for(var i=0;i<max;i++){
      var sum=0;
      if(a.length>i)sum+=a[i];
      if(b.length>i)sum+=b[i];
      c[i]+=sum;
   }
   for(var i=0;i<max;i++){
      if(c[i]>=10){
         c[i]-=10;
         c[i+1]++;
      }
   }
   if(c[c.length-1]==0)c.pop();
   var str=c.reverse().join("");
   if(c.length>80)str="overflow";
   console.log(str);
   n--;
}