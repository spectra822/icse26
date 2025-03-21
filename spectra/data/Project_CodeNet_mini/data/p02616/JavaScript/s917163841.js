const [nk, as] = require('fs').readFileSync('/dev/stdin', 'utf8').split(/\n/)
const [n, k] = nk.split(/\s/).map(Number)
const arr = as.split(/\s/).map(Number).sort((a, b) => Math.abs(b) - Math.abs(a))
const base = BigInt(Math.pow(10, 9) + 7)

let results = [], lowestP = -1, lowestN = -1, odd = false

for (let i = 0; i < k; i++) {
  results.push(arr[i])
  if (arr[i] < 0) {
    lowestN = i
    odd = !odd
  } else {
    lowestP = i
  }
}
if (results[lowestP] === 0) {
  console.log(0)
} else {
  if (odd) {
    let mul1 = lowestP >= 0 ? 1 / results[lowestP] : 0
    let mul2 = lowestN >= 0 ? 1 / -results[lowestN] : 0
    let index1 = -1
    let index2 = -1
    for (let i = k; i < n; i++) {
      if (arr[i] < 0 && index1 < 0 && mul1 !== 0) {
        mul1 *= -arr[i]
        index1 = i
      } else if (arr[i] > 0 && index2 < 0 && mul2 !== 0) {
        mul2 *= arr[i]
        index2 = i
      }
      if ((index1 >= 0 || mul1 === 0) && (index2 >= 0 || mul2 === 0)) {
        break
      }
    }
    const v1 = mul1 * Number(index1 >= 0), v2 = mul2 * Number(index2 >= 0)
    if (index1 < 0 && index2 < 0) {
      results = []
    } else if (v1 > v2) {
      results[lowestP] = arr[index1]
    } else {
      results[lowestN] = arr[index2]
    }
  }
  if (results.length === 0) {
    let result = 1n;
    for (let i = n - 1; i >= n - k; i--) {
      result = (result * BigInt(arr[i])) % base
    }
    console.log((result === 0n ? result : result + base).toString())
  } else {
    let result = 1n;
    for (const r of results) {
      result = (result * BigInt(r)) % base
    }
    console.log(result.toString())
  }
}