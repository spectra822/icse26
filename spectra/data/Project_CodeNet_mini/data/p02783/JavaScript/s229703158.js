'use strict';
function Main(input) {
	input = input.split(" ");
	
	var h = parseInt(input[0], 10);
	var a = parseInt(input[1], 10);
  	var count = 0;
	while(h > 0){
      h -= a;
      count ++;
    }
  console.log(count);
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));