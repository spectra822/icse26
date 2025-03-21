"use strict";
    
const main = arg => {
    arg = arg.trim().split("\n");
    const N = parseInt(arg[0].split(" ")[0]);
    const X = parseInt(arg[0].split(" ")[1]);
    
    let a = [1];
    let p = [1];
    
    for(let i=1; i<N; i++) {
        a.push((a[i-1] * 2) + 3);
        p.push((p[i-1] * 2) + 1);
    }

    const rec = (N, X) => {
        // ベースケース、0枚食べる時以外は必ず１枚
        if(N === 0) {
            return X <= 0 ? 0 : 1;
        // 半分以下の層までしか食べないなら、前のバーガーと同じである
        } else if(X <= 1 + a[N-1]) {
            return rec(N-1, X-1);
        // 半分以上食べる時
        } else {
            return p[N-1] + 1 + rec(N-1, X-2-a[N-1]);
        }
    }
    
    let answer = rec(N, X);
    
    console.log(answer)
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));