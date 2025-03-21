var flag=[];
for(var i=0;i<300000;i++)flag[i]=true;
var ms=[];
var i=1;
while(true){
   var m=(7*i)-1;
   var s=(7*i)+1;
   if(flag[m])ms.push(m);
   if(flag[s])ms.push(s);
   var j=2;
   while(true){
      flag[m*j]=false;
      flag[s*j]=false;
      if(m*j>300000)break;
      j++;
   }
   if(m>300000)break;
   i++;
}
var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
while(true){
   var n=arr.shift()-0;
   if(n==1)break;
   var sqrt=Math.sqrt(n);
   var ans=[];
   var i=0;
   ms.forEach(function(v){
      if(n%v==0)ans.push(v);
   });
   console.log(n+": "+ans.join(" "));
}