process.stdin.resume();
process.stdin.setEncoding('utf8');

var lines = [];
var reader = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
reader.on('line', (line) => {
  lines.push(line);
});
reader.on('close', () => {
    const [A,B,C] = lines[0].split(" ").map(v=>BigInt(v));
    if(A%2n==0n||B%2n==0n||C%2n==0n){
        console.log(0);
    }else{
        console.log(min(A*B,B*C,A*C).toString());
    }
});

min = (...a)=>{return a.reduce((a,b)=>a<b?a:b, a[0])};
