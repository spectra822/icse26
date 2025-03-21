function main(input) {
  const args = input.split(' ').map(n => parseInt(n, 10));
  const S = (args[0] * args[1]) / 2;
  console.log(S);
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'));