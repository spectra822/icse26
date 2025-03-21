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
    const N = lines[0]-0;
    const t = lines[1].split(" ").map(v=>v-0);
    const tsum = t.reduce((a,b)=>a+b, 0);
    const M = lines[2];
    const px = lines.filter((v,i)=>i>2).map(v=>v.split(" ").map(v=>v-0));
    px.forEach(([p, x])=>{
        console.log(tsum-t[p-1]+x);
    })
});
