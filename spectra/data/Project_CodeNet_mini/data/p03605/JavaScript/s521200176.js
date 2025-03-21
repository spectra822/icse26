const main = stdin => {
  const input = stdin.trim().split('\n')
  const N = input[0]

  if (N[0] === '9' || N[1] === '9') {
    console.log('Yes')
  } else {
    console.log('No')
  }
}


// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
