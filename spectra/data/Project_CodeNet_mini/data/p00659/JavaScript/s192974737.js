var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
while(true){
   var n=arr.shift()-0;
   if(n===0)break;
   var tv=[];
   for(var i=0;i<30;i++)tv[i]=0;
   var obj={};
   for(var i=0;i<n;i++){
      var ary=arr.shift().split(" ");
      var name=ary.shift();
      ary.shift();
      obj[name]=ary.map(Number);
      ary.forEach(function(v){tv[v]++;});
   }
   var ans=[];
   for(var k in obj){
      var sum=0;
      obj[k].forEach(function(v){
         sum+=(n+1)-tv[v];
      });
      ans.push([sum,k]);
   }
   ans.sort(function(a,b){
      if(a[0]==b[0])return a[1]>b[1];
      else return a[0]-b[0];
   });
   console.log(ans[0][0]+" "+ans[0][1]);
}