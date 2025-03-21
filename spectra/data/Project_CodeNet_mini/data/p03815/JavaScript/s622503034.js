'use strict'

function main(input) {
  const x = Math.floor(input / 11)
  if (input % 11 > 6) console.log(x * 2 + 2)
  else if (input % 11 > 0) console.log(x * 2 + 1)
  else console.log(x * 2)
}

main(require("fs").readFileSync("/dev/stdin", "utf8"));