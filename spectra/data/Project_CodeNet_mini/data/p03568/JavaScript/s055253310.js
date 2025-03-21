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
    const N = lines[0];
    const list = lines[1].split(" ").map(v=>v-0);
    const cnt = list.filter(v=>v%2==0).length;
    console.log(Math.pow(3,N)-Math.pow(2,cnt));
});

