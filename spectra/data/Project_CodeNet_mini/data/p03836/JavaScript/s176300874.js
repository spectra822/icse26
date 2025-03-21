function main(lines) {
  const [sx, sy, tx, ty] = splitN(lines[0]);

  const dx = tx-sx, dy = ty-sy;
  let s = '';
  s += 'U'.repeat(dy) + 'R'.repeat(dx);
  s += 'D'.repeat(dy) + 'L'.repeat(dx);
  s += 'L' + 'U'.repeat(dy+1) + 'R'.repeat(dx+1) + 'D';
  s += 'R' + 'D'.repeat(dy+1) + 'L'.repeat(dx+1) + 'U';

  return s;
}


const ans = main( require("fs").readFileSync("/dev/stdin", "utf8").trim().split("\n") );
console.log( ans );

function splitN(s) {
  return s.split(' ').map(Number);
}