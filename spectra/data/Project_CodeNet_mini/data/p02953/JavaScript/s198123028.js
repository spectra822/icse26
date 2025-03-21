function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const N=input[0].split(' ')[0]-0;
  const H=input[1].split(' ').map(e=>{
    return e-0;
  });
  var max=Infinity;
  for(var i=N-1;i>=0;i--){
    if(H[i]<=max){
      max=H[i];
    }else if(H[i]>max+1){
      console.log('No');
      return;
    }
  }
  console.log('Yes');

}

//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));