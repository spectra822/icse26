console.log((args=>{
  const [HW,...A] = args.trim().split('\n');
  const [H,W] = HW.split(' ').map(v=>v|0);
  let stack = [], _stack = [], count = 0;
  const map = Array.from({length:H},_=>Array(W).fill(false));
  for ( let i = 0; i < H; i++ ) {
    for ( let j = 0; j < W; j++ ) {
      if ( A[i][j] === '#' ) {
        stack.push([i,j]);
        map[i][j] = true;
      }
    }
  }
  const dir = [[-1,0],[0,-1],[1,0],[0,1]];
  while ( stack.length ) {
    const [i,j] = stack.pop();
    for ( const [di,dj] of dir ) {
      const h = i+di, w = j+dj;
      if ( h < 0 || H <= h || w < 0 || W <= w || map[h][w] ) continue;
      map[h][w] = true;
      _stack.push([h,w]);
    }
    if ( stack.length === 0 ) {
      [stack,_stack] = [_stack,[]];
      count++;
    }
  }
  return `${count-1}`;
})(require('fs').readFileSync('/dev/stdin', 'utf8')));
