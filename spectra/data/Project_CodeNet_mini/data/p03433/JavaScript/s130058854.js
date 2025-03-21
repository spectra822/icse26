// JavaScript source code
"use strict";

let myFunc = (input) => {
    input = input.split("\n");
    let N = parseInt(input[0]);
    let A = parseInt(input[1]);
    for(let i = 0; i <= A; i++){
        if(i > N) break;
        if((N - i) % 500 === 0){
            console.log("Yes");
            return 0;
        }
    }
    console.log("No");
};

myFunc(require("fs").readFileSync("/dev/stdin", "utf8"));