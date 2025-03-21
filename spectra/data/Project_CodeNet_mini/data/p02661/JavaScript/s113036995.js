console.log((args=>{
  const [[N],...X] = args.trim().split('\n').map(r=>r.split(' ').map(v=>v|0));
  const A = [], B = [];
  for ( let i = 0; i < N; i++ ) {
    A.push(X[i][0]);
    B.push(X[i][1]);
  }
  A.sort((a,b)=>a-b);
  B.sort((a,b)=>a-b);
  if ( N&1 ) {
    const m = (N-1)/2;
    return B[m] - A[m] + 1;
  } else {
    const m = N/2;
    return B[m] + B[m-1] - A[m] - A[m-1] + 1;
  }
})(require('fs').readFileSync('/dev/stdin', 'utf8')));
