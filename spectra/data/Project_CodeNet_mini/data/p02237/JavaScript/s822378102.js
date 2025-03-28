(function main() {
  const lines = require('fs').readFileSync('/dev/stdin', 'utf8').trim().split('\n');
  const n = Number(lines.shift());
  const res = Array.from(Array(n), () => Array.from(Array(n), () => 0));

  lines.forEach((l, i) => l.split(' ').splice(2).forEach(e => res[i][e-1] = 1));
  console.log(res.map(r => r.join(' ')).join('\n'));
})();

