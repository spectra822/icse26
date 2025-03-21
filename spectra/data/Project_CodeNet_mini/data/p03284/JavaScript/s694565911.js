const main = (arg) => {
  const lines = arg.trim().split('\n');
  const [N, K] = lines[0].split(' ').map(Number);
  console.log(N % K === 0 ? 0 : 1);
};
main(require('fs').readFileSync('/dev/stdin', 'utf8'));
