console.log((args=>{
  const [n,S] = args.trim().split`\n`;
  const N = n|0;
  let r = 0, l = 0;
  for ( let i = N; i--;) l += (S[i]===')')?1:l?-1:0;
  for ( let i = 0; i < N; i++) r += (S[i]==='(')?1:r?-1:0;
  return '('.repeat(l) + S + ')'.repeat(r);
})(require('fs').readFileSync('/dev/stdin', 'utf8')));
