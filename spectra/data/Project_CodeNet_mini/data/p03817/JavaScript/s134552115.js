"use strict";
    
const main = arg => {
    arg = arg.trim().split("\n");
    const N = parseInt(arg[0].split(" ")[0]);
  	
  	let temp = Math.floor(N / 11);
  	let rest = N % 11;
  	
//   	console.log(temp)
//   	console.log(rest)
//     console.log(temp * 11)
    
//     console.log(temp * 2)

    console.log((temp * 2) + Math.ceil(rest / 6));
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));
