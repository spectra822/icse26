var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
while(true){
   var np=Arr.shift();
   if(np=="0 0")break;
   np=np.split(" ").map(Number);
   var n=np[0];
   var p=np[1];
   var arr=[];
   for(var i=0;i<n;i++)arr.push(0);
   var j=0;
   for(var i=0;i<1000000;i++){
      if(j==arr.length)j=0;
      if(p>0){
         p--;
         arr[j]++;
         if(p==0){
            var sum=arr.reduce(function(a,b){return a+b;});
            if(sum-arr[j]==0){console.log(j);break;}
         }
      }else{
         p=arr[j];
         arr[j]=0;
      }
      j++;
   }
}