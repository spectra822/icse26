const main = stdin => {
  const input = stdin.trim().split('\n')

  const [A, B] = input[0].split(' ').map(x => parseInt(x))
  console.log(Math.max(A + B, A - B, A * B))
}

// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
