function bigAdd(x,y){
   var a=(x+"").split("").reverse().map(Number);
   var b=(y+"").split("").reverse().map(Number);
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
   return str;
}

var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
arr.shift();
var a=arr.shift().split(" ").map(Number);
a.sort(function(a,b){return a-b;});
arr.shift();
var b=arr.shift().split(" ").map(Number);
var c=arr.shift().split(" ");
var ary=[];
for(var i=0;i<=1000000;i++)ary[i]=false;
ary[0]=0;
var sum=0;
a.forEach(function(v){
   sum=bigAdd(sum,v);
   ary[v]=sum;
});
b.forEach(function(v,i){
   while(true){
      if(ary[v]!==false)break;
      v--;
   }
   var ans="No";
   if(c[i]==ary[v]){ans="Yes";}  
   else if(c[i].length<ary[v].length){ans="Yes";}
   else if(c[i].length==ary[v].length){
      for(var j=0;j<c[i].length;j++){
         if(c[i][j]-0===ary[v][j]-0){continue;}
         else if(c[i][j]-0>ary[v][j]-0){ans="No";break;}
         else if(c[i][j]-0<ary[v][j]-0){ans="Yes";break;}
      }
   }
   console.log(ans);
});