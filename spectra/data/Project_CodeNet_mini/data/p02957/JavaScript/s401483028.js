const main = stdin => {
  const input = stdin.trim().split('\n')

  const [A, B] = input[0].split(' ').map(x => parseInt(x))
  if (A % 2 !== B % 2) {
    console.log('IMPOSSIBLE')
    return
  }

  console.log((A + B) / 2)
}

// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
