

function Main(input) {
  input=input.split("\n");
  if(input[input.length-1]===''){
    input.pop();
  }
  const N=input[0].split(' ')[0]-0;
  const S=input[1].split(' ').map(e=>{
    return e-0;
  });
  var max=0;
  var previous=0;
  var temp=0;
  for(var i=0;i<N;i++){
    if(previous>=S[i]){
      temp++;
    }else{
      max=Math.max(max,temp);
      temp=0;
    }
    previous=S[i];
  }
  max=Math.max(max,temp);
  
  console.log(max);
 
}




//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));