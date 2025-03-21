const input = require("fs").readFileSync("/dev/stdin", "utf8")
const lines = input.split('\n')
const [A, B, N] = lines[0].split(' ').map(Number)

const x = Math.min(N, B - 1)
const res = Math.floor(A * x / B) - A * Math.floor(x / B)

console.log(res)