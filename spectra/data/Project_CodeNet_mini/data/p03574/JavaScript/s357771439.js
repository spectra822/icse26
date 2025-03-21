"use strict"
const create = () => {
    const input = require("fs").readFileSync("/dev/stdin", "utf8").trim().split("\n");
    const res = {
        "list": input, "index": 0, "max": input.length,
        "hasNext": function () { return this.index < this.max },
        "next": function () { if (!this.hasNext()) { throw "ArrayIndexOutOfBoundsException"; } else { return this.list[this.index++]; } }
    };
    return res;
}
const o = create();
const next = () => o.next()
const nextInt = () => parseInt(o.next())
const nextStrArray = () => o.next().split(" ")
const nextIntArray = () => o.next().split(" ").map(el => parseInt(el))
const nextCharArray = () => o.next().split("")
const hasNext = () => o.hasNext()
const myout = (...x) => console.log(...x)
const Main = () => {
    let [h, w] = nextIntArray()
    let s = []
    while (hasNext()) {
        s.push(next())
    }
    let a = Array.from( new Array(h), _ => new Array(w).fill(0))
    let dir = [
        [-1, -1],
        [-1, 0],
        [-1, 1],
        [0, -1],
        [0, 1],
        [1, -1],
        [1, 0],
        [1, 1],
    ]
    for (let i = 0; i < s.length; i++) {
        for (let j = 0; j < s[i].length; j++) {
            if (s[i][j] == "#") {
                a[i][j] = "#"
            } else {
                let cnt = 0
                for (let d of dir) {
                    let x = j + d[0]
                    let y = i + d[1]
                    if (0 <= x && x < s[0].length && 0 <= y && y < s.length) {
                        if (s[y][x] == "#") cnt++
                    }
                }
                a[i][j] = cnt
            }
        }
    }
    for (let l of a) {
        console.log(l.join(""))
    }
}
Main()

