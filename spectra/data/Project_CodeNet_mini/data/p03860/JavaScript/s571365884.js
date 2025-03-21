function main(input) {
  console.log('A'+input.substring(8,9)+'C');
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));
