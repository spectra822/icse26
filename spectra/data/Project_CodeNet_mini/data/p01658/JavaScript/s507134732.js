var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var mn=arr.shift().split(" ").map(Number);
var cnt=0;
for(var i=0;i<mn[0];i++){
   var str=arr.shift();
   if(i!=0)str=str.replace(/0/g,"a").replace(/1/g,"b").replace(/b/g,"0").replace(/a/g,"1");
   var ary=str.split(" ").map(Number);
   while(true){
      if(ary[0]==1){
         cnt++;
         ary.shift();
         if(ary.length==0)break;
         if(ary[0]==0)ary[0]=1;
         else ary[0]=0;
      }else if(ary[ary.length-1]==1){
         cnt++;
         ary.pop();
         if(ary.length==0)break;
         if(ary[ary.length-1]==0)ary[ary.length-1]=1;
         else ary[ary.length-1]=0;
      }else{
         ary.shift();
         if(ary.length==0)break;
         if(ary[0]==0)ary[0]=1;
         else ary[0]=0;
      }
   }
}
console.log(cnt);