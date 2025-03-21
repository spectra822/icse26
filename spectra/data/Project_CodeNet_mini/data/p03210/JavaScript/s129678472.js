function main(arg) {
  const input = arg.trim().split('\n');
  const x = Number(input[0]);
  if (x === 7 || x === 5 || x === 3) {
    console.log('YES');
  } else {
    console.log('NO');
  }
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));
