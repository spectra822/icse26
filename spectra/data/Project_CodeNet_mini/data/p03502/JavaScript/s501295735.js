// https://atcoder.jp/contests/abc080/tasks/abc080_b
"use strict";
function Main(input) {
  const X = Number(input);
  const sum = input.split("").reduce((acc, cur) => Number(acc) + Number(cur), 0);

  if (X % sum === 0) {
    console.log("Yes");
  } else {
    console.log("No");
  }
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
