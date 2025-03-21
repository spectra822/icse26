console.log((args=>{
  const [_N,s,t] = args.trim().split`\n`, N = _N|0;
  S: for ( let i = 0; i < N; i++ ) {
    for ( let j = 0; i+j < N; j++ ) {
      if ( s[i+j] !== t[j] ) continue S;
    }
    return i + N;
  }
  return N+N;
})(require('fs').readFileSync('/dev/stdin', 'utf8')));
