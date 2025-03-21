function main(input) {
  const args = input.split(' ');
  const K = parseInt(args[0], 10);
  const S = parseInt(args[1], 10);
  
  let count = 0;
  
  for (let x = 0; x <= K; x++) {
    for (let y = 0; y <= K; y++) {
      z = S - x - y;
      if (0 <= z && z <= K) { count++; }
    }
  }
  
  console.log(count);
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'));