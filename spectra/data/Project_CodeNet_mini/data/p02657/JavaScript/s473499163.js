function Main(input) {
  input = input.split("\n");
  const A = parseInt(input[0].split(" ")[0]);
  const B = parseInt(input[0].split(" ")[1]);

  console.log(A * B);
}
// デバッグ用
function debug() {
  var input = document.getElementById("input").value;
  Main(input);
}

//* この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));