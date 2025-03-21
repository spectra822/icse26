function gerTheNumberOfCoin(){
   var T=[];
   for(var i=0;i<=n;i++){
      T[i]=Number.POSITIVE_INFINITY;
    }
    T[0]=0;    
    for(var i=0;i<m;i++){    
       for(var j=C[i];j<=n;j++){
          T[j]=Math.min(T[j],T[j-C[i]]+1);
       }
    }
    return T[n];
}

var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var nm=Arr[0].split(" ").map(Number);
var n=nm[0];
var m=nm[1];
var C=Arr[1].split(" ").map(Number);
var min=gerTheNumberOfCoin();
console.log(min);