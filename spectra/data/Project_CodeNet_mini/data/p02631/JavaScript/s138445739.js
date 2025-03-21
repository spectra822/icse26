const readLines = (input) => input.split('\n')
const println = (value) => console.log(value)
const readInt = (input) => parseInt(input, 10)
const readIntList = (input) => input.split(' ').map(n => parseInt(n, 10))
const naturalOrder = (a, b) => {
    if (b == a) return 0
    return (a < b) ? -1 : 1
}

function main(input) {
    const lines = readLines(input)
    const n = readInt(lines[0])
    const aArray = readIntList(lines[1])
    const allXor = aArray.reduce((acc, a) => acc ^ a)
    const ans = aArray.map((a, i) => a ^ allXor).join(' ')
    println(ans)
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'));
