console.log((args=>{
  const [[N,M],...tmp] = args.trim().split`\n`.map(r=>r.split` `.map(v=>v|0));
  const G = Array.from({length:N+1},_=>[]);
  for ( let i = 0; i < M; i++ ) {
    const [a,b] = tmp[i];
    G[a].push(b);
    G[b].push(a);
  }
  for ( const x of G[1] ) {
    for ( const t of G[x] ) {
      if ( t === N ) return 'POSSIBLE';
    }
  }
  return 'IMPOSSIBLE';
})(require('fs').readFileSync('/dev/stdin', 'utf8')));
