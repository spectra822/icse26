"use strict"
var Main=function(input){
  input=input.split('\n');
  var L=parseInt(input.shift());
  var parity=[];
  var a=[];
  var b=[];
  var c=[];
  for(let i=0;i<L;i++){
    if(input[i]==='0')parity[i]=0;
    else{
      parity[i]=parseInt(input[i][input[i].length-1]);
      parity[i]=(parity[i]%2===0)?2:1;
    }
    input[i]=parseInt(input[i]);
    a[i]=input[i];
    b[i]=2-parity[i];
    c[i]=(parity[i]===1)?0:1;
  }

var dp=[];
  dp[0]=[0,0,0,0,0];
  for(let i=0;i<L;i++){
    dp[i+1]=[];
    dp[i+1][0] = dp[i][0]+a[i];
    dp[i+1][1] = Math.min(dp[i+1][0],dp[i][1]+b[i]);
    dp[i+1][2] = Math.min(dp[i+1][1],dp[i][2]+c[i]);
    dp[i+1][3] = Math.min(dp[i+1][2],dp[i][3]+b[i]);
    dp[i+1][4] = Math.min(dp[i+1][3],dp[i][4]+a[i]);
  }
  console.log(dp[L][4]);
}

Main(require('fs').readFileSync('/dev/stdin','utf8'));