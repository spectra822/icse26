// inputに入力データ全体が入る
function Main(input) {
  input = input.split('\n');
  var str = input[1].split('').sort();
  var firstR = str.indexOf('R');

  if (parseInt(input[0]) * .5 - firstR <= 0){
    console.log('No')
  } else {
    console.log('Yes')
  }
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));