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
    const [N, A, B] = lines[0].split(" ").map(v=>BigInt(v));
    console.log(calc(N, A, B).toString());
});
calc = (N, a, b)=>{
    if(abs(a,b)%2n==0n) return abs(a,b)/2n;
    if(a==1n) return min(b-1n, calc(N, a, b-1n)+1n);
    if(b==1n) return min(a-1n, calc(N, b, a-1n)+1n);
    if(a==N) return calc(N, N-a+1n, N-b+1n);
    if(b==N) return calc(N, N-a+1n, N-b+1n);
    if(a==b) return 0;
    if(a>b){
        return min(
            calc(N, a-(b-1n), 1n) + (b-1n),
            calc(N, N, b+(N-a)) + (N-a)
        );
    }else{
        return min(
            calc(N, a+(N-b), N) + (N-b),
            calc(N, 1n, b-(a-1n)) + (a-1n)
        );
    }
}
abs = (a,b)=>{return a<b?(b-a):(a-b)}
min = (...a)=>{return a.reduce((a,b)=>a<b?a:b, a[0])};
max = (a,b)=>{return a>b?a:b};
