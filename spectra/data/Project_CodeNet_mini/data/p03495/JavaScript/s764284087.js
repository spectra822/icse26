// https://atcoder.jp/contests/abc081/tasks/arc086_a
"use strict";
function Main(input) {
  const params = input.trim().split("\n");
  const [N, K] = params[0].trim().split(" ").map(Number);
  const A = params[1].trim().split(" ").map(Number);
  const counts = Array(N + 1).fill(0);

  for (let i = 0; i < N; i++) {
    counts[A[i]] = counts[A[i]] + 1;
  }
  const filterdCounts = counts.sort((a, b) => a - b).filter((a) => a);
  if (filterdCounts.length <= K) {
    console.log(0);
    return;
  }

  let rewriteCount = 0;
  let change = filterdCounts.length - K;
  for (let i = 0; i < change; i++) {
    rewriteCount += filterdCounts[i];
  }
  console.log(rewriteCount);
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
