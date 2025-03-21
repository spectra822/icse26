var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
while(true){
   var NTLB=arr.shift().split(" ").map(Number);
   if(NTLB.join(" ")=="0 0 0 0")break;
   var N=NTLB[0];
   var T=NTLB[1];
   var arrL=[];
   for(var i=0;i<NTLB[2];i++)arrL.push(arr.shift()-0);
   var arrB=[];
   for(var i=0;i<NTLB[3];i++)arrB.push(arr.shift()-0);
   var dp=[];
   for(var i=0;i<=T;i++){
      dp[i]=[];
      for(var j=0;j<=N;j++){
         dp[i][j]=0;
      }
   }
   dp[0][0]=1;
   for(var i=1;i<=T;i++){
      for(var j=0;j<N;j++){
         for(var k=1;k<=6;k++){
            var I=i;
            var jk=j+k;
            if(jk>N)jk=N-(jk-N);
            var flagL=arrL.some(function(v){
               if(v==jk)return true;
            });
            if(flagL && I!=T)I=I+1;
            var flagB=arrB.some(function(v){
               if(v==jk)return true;
            });
            if(flagB)jk=0;
            dp[I][jk]+=dp[i-1][j]/6;
         }
      }
   }
   var ans=0;
   for(var i=1;i<=T;i++)ans+=dp[i][N];
   console.log(ans.toFixed(6));
}