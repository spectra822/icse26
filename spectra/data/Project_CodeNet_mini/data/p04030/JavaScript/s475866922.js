function main(input) {
  const S = input.toString().split('');
  let result = [];
  for (let i = 0; i < S.length; i++) {
    switch (S[i]) {
      case '0':
        result.push('0');
        break;
      case '1':
        result.push('1');
        break;
      case 'B':
        if (result.length > 0 ) { result.pop(); }
        break;
      default:
        break;
     }
  }
  console.log(result.join(''));
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'));