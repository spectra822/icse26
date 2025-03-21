const main = args => {
  const [a, b, c, x] = args.split('\n').map(arg => Number(arg));
  let ans = 0;
  [...Array(a+1)].forEach((_, i) => { [...Array(b+1)].forEach((_, j) => { [...Array(c+1)].forEach((_, k) => { if (500 * i + 100 * j + 50 * k === x) ++ans }) }) });
  
  console.log(ans);
};
main(require('fs').readFileSync('/dev/stdin', 'utf8'));