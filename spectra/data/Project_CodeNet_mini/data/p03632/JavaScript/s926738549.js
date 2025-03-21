function Main(input) {
  const lines = input.split('\n');
  const [a, b, c, d] = lines[0].split(' ').map(s => parseInt(s));
  console.log(Math.max(Math.min(b, d) - Math.max(a, c), 0));
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));