const main = (input) => {
  input = input.trim().split('\n')
  const [n, m, k] = input[0].split(' ').map(BigInt)
  const a = input[1].split(' ').map(BigInt)
  const b = input[2].split(' ').map(BigInt)

  const a_read = [], b_read = []
  let a_sum = 0n, b_sum = 0n

  for (let i=0; i<b.length; i++) {
    if (b_sum + b[i] <= k) {
      b_read.push(b[i])
      b_sum += b[i]
    }
    else break
  }

  let ans = b_read.length

  for (let i=0; i<a.length; i++) {
    a_read.push(a[i])
    a_sum += a[i]

    while (a_sum + b_sum > k && b_read.length) b_sum -= b_read.pop()

    if (a_sum + b_sum > k) break

    ans = Math.max(ans, a_read.length + b_read.length)
  }

  return console.log(ans)
}

process.env.MYTEST ? test() : main(require('fs').readFileSync('/dev/stdin', 'utf8'))