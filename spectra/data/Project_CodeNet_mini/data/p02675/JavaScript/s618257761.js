function Main(input) {
  input = input.split("\n");
  const N = input[0];
  const n = N[N.length - 1];

  if (n === '3') {
    console.log('bon');
  } else if (n === '0' || n === '1' || n === '6' || n === '8') {
    console.log('pon');
  } else {
    console.log('hon');
  }

}

// デバッグ用
function debug() {
  var input = document.getElementById("input").value;
  Main(input);
}

//* この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));