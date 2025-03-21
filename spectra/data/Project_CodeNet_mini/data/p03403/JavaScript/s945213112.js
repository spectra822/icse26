"use strict"
const create = () => {
    const input = require("fs").readFileSync("/dev/stdin", "utf8").trim().split("\n");
    const res = {
        "list": input, "index": 0, "max": input.length,
        "hasNext": function() {return this.index < this.max},
        "next": function() { if (!this.hasNext()) {throw "ArrayIndexOutOfBoundsException";}else{return this.list[this.index++];}}
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
    let n = nextInt()
    let a = [0]
    a.push(...nextIntArray())
    a.push(0)
    let total = 0
    for(let i = 1; i<a.length; i++){
        total += Math.abs(a[i] - a[i-1])
    }
    for(let i = 1; i<a.length-1; i++){
        console.log(total - Math.abs(a[i] - a[i-1]) - Math.abs(a[i+1]-a[i]) + Math.abs(a[i+1] - a[i-1]))
    }
}
Main()

