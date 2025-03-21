'use strict';
function Main(input) {
  input = input.split(" ");
  let a = parseInt(Math.max.apply(null, input));
  let b = parseInt(Math.min.apply(null, input)); 
  let result = a * b;
  let mod=1;
  while(mod > 0){
    mod = a % b;
    a = b;
    b = mod;
  }
                   
  console.log(result / a);  	
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));