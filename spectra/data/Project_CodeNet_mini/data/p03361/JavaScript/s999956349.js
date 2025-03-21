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
    const [H,W] = nextIntArray()
    let s = []
    while(hasNext()){
        s.push(next().split(""))
    }
    let dir = [[1,0],[-1,0],[0,1],[0,-1]]
    for(let i = 0; i<H; i++){
        for(let j = 0; j<W; j++){
            if(s[i][j] == "#"){
                let res = false
                for(let el of dir){
                    let x = i+el[0]
                    let y = j+el[1]
                    if(x < 0 || x>=H || y<0|| y>=W) continue
                    if(s[x][y] == "#" || s[x][y] == "X"){
                        res = true
                        s[i][j] = "X"
                    } 
                }
                if(res == false){
                    console.log("No")
                    return
                }
            }
        }
    }
    console.log("Yes")
}
Main()
