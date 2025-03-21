const main = stdin => {
  const input = stdin.trim().split('\n')
  const N = parseInt(input[0])

  const cards = input[1].split(' ').map(x => parseInt(x))
  const sortedCards = cards.sort((a, b) => b - a)
  const alices = sortedCards.filter((a, i) => i % 2 === 0).reduce((a, b) => a + b)
  const bobs = sortedCards.filter((a, i) => i % 2 !== 0).reduce((a, b) => a + b)

  console.log(alices - bobs)
}


// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"))
