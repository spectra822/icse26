function main(input) {
  input = input.trim();
  const [a,b,c,d] = input.split('\n').map(Number);
  console.log(a>b ? b*c+(a-b)*d : a*c);
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));