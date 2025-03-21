const main = stdin => {
  const input = stdin.trim().split('\n')

  const [A, B, C] = input[0].split(' ').map(x => parseInt(x))
  console.log(Math.max(C - (A - B), 0));
}

// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
