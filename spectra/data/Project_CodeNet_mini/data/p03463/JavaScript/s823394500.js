const input = require("fs").readFileSync("/dev/stdin", "utf8")

;(input => {

    const lines = input.split('\n')
    const [N, A, B] = lines[0].split(' ').map(Number)

    const diff = Math.abs(A - B)

    console.log(diff % 2 ? 'Borys' : 'Alice')

})(input)
