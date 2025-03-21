const input = require("fs").readFileSync("/dev/stdin", "utf8")
;(input => {

    const lines = input.split('\n')
    const [X, Y, A, B, C] = lines[0].split(' ').map(Number)
    const p = lines[1].split(' ').map(Number).sort((a, b) => a - b)
    const q = lines[2].split(' ').map(Number).sort((a, b) => a - b)
    const r = lines[3].split(' ').map(Number).sort((a, b) => a - b)

    const S = [
        ...p.splice(A - X, X),
        ...q.splice(B - Y, Y),
        ...r
    ]

    S.sort((a, b) => b - a)

    let ans = 0
    for (let i = 0; i < X + Y; i++) {
        ans += S[i]
    }

    console.log(ans)

})(input)
