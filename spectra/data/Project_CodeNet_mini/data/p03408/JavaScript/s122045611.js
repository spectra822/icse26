function main(input) {
  const args = input.split('\n');
  const N = parseInt(args[0], 10);
  const M = parseInt(args[N + 1], 10);
  data = {};
  let blues = [];
  let reds = [];
  let ans;
  
  for (let i = 1; i <= N; i++) {
    blues.push(args[i]);
  }
  
  for (let i = (N + 2); i <= (N + M + 1) ; i++) {
  	reds.push(args[i]);
  }
  
  for (let i = 0; i < blues.length; i++) {
    key = blues[i];
    data[key] = data[key] ? data[key] + 1 : 1;
  }
  
  for (let i = 0; i < reds.length; i++) {
  	key = reds[i];
    data[key] = data[key] ? data[key] - 1 : -1;
  }
  
  for (key in data) {
    if (!ans || data[key] > ans) { 
      ans = data[key];
    }
  }
  
  if (ans < 0) {
    console.log(0);
  } else {
    console.log(ans);
  }
}

main(require('fs').readFileSync('/dev/stdin', 'utf8'));