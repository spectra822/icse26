function Main(input) {
  const numbers = input.split(' ');
  for (var i=0; i<numbers.length; i++) {
    if (numbers[i] == 0) {
      const ans = i + 1;
      console.log(ans.toString());
      break;
    }
  }
}

//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require('fs').readFileSync('/dev/stdin', 'utf8'));
