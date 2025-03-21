function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const N=input[0]-0;
  const X=input[1].split(' ').map(e=>{
    return e-0;
  });
  var sum=0;
  X.forEach(e=>{
    sum+=e;
  });
  var p=Math.round(sum/N);
  sum=0;
  X.forEach(e=>{
    sum+=(e-p)**2;
  });
  console.log(sum);
}


//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
  



  
