function permutation(n,k){
    var ret=[[]];
    var next;
    for(var i=0;i<k;i++){
        next=[];
        ret.forEach(e=>{
            for(var k=1;k<=n;k++){
                if(!e.includes(k)){
                    next.push(e.concat([k]));
                }
            }
        });
        ret=next.concat([]);
    }
    return ret;
}

function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  var X=input[0].split(' ')[0]-0;
  loop1:
  while(true){
    for(var i=2;i**2<=X;i++){
      if(X%i===0){
        X++;
        continue loop1;
      }
    }
    console.log(X);
    return;
  }
}


//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));