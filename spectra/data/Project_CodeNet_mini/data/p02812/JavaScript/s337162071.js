
function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const N=input[0].split(' ')[0]-0;
  const S=input[1];
  var ans=0;
  for(var i=0;i<=S.length-3;i++){
    if(S.slice(i,i+3)==='ABC'){
      ans++;
    }
  }
  console.log(ans);
}


//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
  



  
