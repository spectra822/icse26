function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const S=input[0];
  const MOD=10**9+7;
  var possibility=new Array(13);
  possibility.fill(0);
  if(S[S.length-1]==='?'){
    for(var i=0;i<=9;i++){
      possibility[i]=1;
    }
  }else{
    possibility[S[S.length-1]-0]=1;
  }
  var ten=1;
  var next;
  for(var j=S.length-2;j>=0;j--){
    ten=ten*10%13;
    next=new Array(13);
    next.fill(0);
    if(S[j]==='?'){
      for(var i=0;i<13;i++){
        [0,1,2,3,4,5,6,7,8,9].forEach(e=>{
          next[(i+ten*e)%13]+=possibility[i];
        });
      }
    }else{
      for(var i=0;i<13;i++){
        next[(i+ten*(S[j]-0))%13]=possibility[i];
      }
    }
    possibility=next.slice().map(e=>{
      return e%MOD;
    });
  }
  console.log(possibility[5]);
}

//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));