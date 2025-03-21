const arr = require('fs').readFileSync('/dev/stdin', 'utf8').split('\n').map((n,i) => [Number(n), i]);
while(([n,i] = arr.shift())[0] !== 0)
console.log(`Case ${i+1}: ${n}`);
