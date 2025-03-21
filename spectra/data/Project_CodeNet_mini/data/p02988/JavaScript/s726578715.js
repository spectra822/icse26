const main = input => {
  const inputs = input.trim().split('\n')
  const n = parseInt(inputs[0])
  const sequence = inputs[1].split(' ').map(a => parseInt(a))

  let count = 0
  for (let i = 1; i < n - 1; i++) {
    if (sequence[i] > Math.min(sequence[i - 1], sequence[i + 1]) && sequence[i] < Math.max(sequence[i - 1], sequence[i + 1])) {
      count++
    }
  }

  console.log(count)
}

// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
