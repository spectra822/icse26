

function Main(input) {
  input = input.split("\n");
  var N = parseInt(input[0].split(" ")[0]);
  var A = parseInt(input[0].split(" ")[1]);
  var x = input[1].split(" ").map(i => parseInt(i));
  var sum=0;
  for(var i=0;i<N;i++){
    sum+=x[i];
  }
  var map=new Array(sum+1);
  for(var i=0;i<sum+1;i++){
    var tmp=new Array(N+1).fill(0);
    
    map[i]=tmp;
  }
  map[0][0]=1;
  for(var k=0;k<N;k++){
    for(var i=N;i>0;i--){
      for(var j=sum+1;j-x[k]>=0;j--){
        if(map[j-x[k]][i-1]!=0){
          map[j][i]=map[j][i]+map[j-x[k]][i-1];
        }
      }
    }
  }
  var ans=0;
  for(var i=1;i<=N;i++){
    if(i*A<=sum){
      ans+=map[i*A][i];
    }
  }
  console.log('%s', ans);
  return ans;
}

function debug(n){
  var input = document.getElementById("input"+n).value;
  var ans=Main(input);
  var result="WA";
  if(ans==document.getElementById("output"+n).value.split("\n")[0]){
    result="AC";
  }
  document.getElementById("result"+n).innerHTML=result;
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));