const input = require("fs").readFileSync("/dev/stdin", "utf8")
const lines = input.split('\n')
const [N, M] = lines[0].split(' ').map(Number)

const map = Array(N + 1).fill().map(_ => [])

for (let i = 1; i <= M; i++) {
    const [A, B] = lines[i].split(' ').map(Number)
    map[A].push(B)
    map[B].push(A)
}

const ans = Array(N + 1).fill(0)

let next = [1]
let i = 0
while (i = next.shift()) {
    for (let j = 0; j < map[i].length; j++) {
        if (!ans[map[i][j]]) {
            ans[map[i][j]] = i
            next.push(map[i][j])
        }
    }
}

ans[1] = 'Yes'
for (let i = 2; i <= N; i++) {
    if (!ans[i]) {
        ans[1] = 'No'
        break
    }
}
if (ans[1] === 'No') {
    console.log('No')
} else {
    ans.shift()
    console.log(ans.join("\n"))    
}