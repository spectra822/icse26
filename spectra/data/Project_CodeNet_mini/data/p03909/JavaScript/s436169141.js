'use strict'

const main = (INPUT) => {
  const input = INPUT.split('\n')
  const abc = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
  for (let i = 1; i < input.length; i++) {
    const S = input[i].split(' ')
    for (let j = 0; j < S.length; j++) {
      if (S[j] == 'snuke') {
        console.log(abc[j] + i)
        return
      }
    }
  }
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'))
