// inputに入力データ全体が入る
function Main(input) {
  // 1行目がinput[0], 2行目がinput[1], …に入る
  input = input.split("\n");
  tmp = input[1].split(" ");
  //配列（ソートで比較する用の宣言）
  var Arrays = [];
  var min;
  var max;

  //文字列から10進数に変換するときはparseIntを使います
  var totalNum = parseInt(input[0], 10);
  for (i = 0; i <= totalNum - 1; i++) {
    Arrays[i] = parseInt(tmp[i], 10);
  }

  min = Math.min(...Arrays);
  max = Math.max(...Arrays);
	
  console.log(max - min);

}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));