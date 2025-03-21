process.stdin.resume();
process.stdin.setEncoding('utf8');
// 自分の得意な言語で
// Let's チャレンジ！！

var lines = [];
var reader = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
reader.on('line', (line) => {
  lines.push(line);
});
reader.on('close', () => {
    const N = lines[0]-0;
    const ansmap = {};
    const limit = Math.sqrt(N);
    for(let x=1;x<limit;x++)
    for(let y=1;y<limit;y++)
    for(let z=1;z<limit;z++){
        const a = x*x+y*y+z*z+x*y+x*z+y*z;
        ansmap[a] = (ansmap[a]||0)+1;
    }
    for(let i=1;i<=N;i++){
      console.log(ansmap[i]||0);
    }
});
