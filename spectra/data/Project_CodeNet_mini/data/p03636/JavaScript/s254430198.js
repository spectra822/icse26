const main = args => {
  const s = args.trim();
  const l = s.length;
  console.log(`${s[0]}${l - 2}${s[l - 1]}`)
};
main(require('fs').readFileSync('/dev/stdin', 'utf8'));