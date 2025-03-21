
function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const N=input[0].split(' ')[0]-0;
  const K=input[0].split(' ')[1]-0;
  var key=input[1].split(' ').map(e=>{
    return e-0;
  }).findIndex(e=>{
    return e===1;
  });
  console.log(Math.ceil((N-1)/(K-1)));
}

//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
