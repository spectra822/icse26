function Main(input) {
    input = input.trim().split("\n").map(function(x) { return x.split(" ")});
    var N = parseInt(input[0][0], 10);
    var M = parseInt(input[0][1], 10);
    var K = parseInt(input[0][2], 10);
    var C = 998244353;
    var C2 = 1e+5;
    v = nCr_amari(N - 1, K, C, C2).reverse();
    tmp = fastRuijoR(M - 1, N - K - 1, C, C2);
    var ans = 0;
    for  (var x of v){
        ans += kakeruR(tmp, x, C, C2);
        ans %= C;
        tmp = kakeruR(tmp, M - 1, C, C2);
    }
    ans = kakeruR(ans, M, C, C2);
    console.log(ans);
}

function kakeruR(a, b, C, C2){
    var tmpQ, tmpR, ans;
    tmpQ = (b / C2 | 0);
    tmpR = b - (tmpQ * C2);
    ans = (a * tmpQ % C) * C2 % C + (a * tmpR);
    ans %= C;
    return ans;
}

function nCr_amari(MAX, k, MOD, C2) { //return [maxC0, maxC1, ..., maxCk]
    // 前処理
    var v_ans = [ ];
    var fac, finv, inv;
    fac = [1,1];
    finv = [1,1];
    inv = [0,1];
    for (var i = 2; i <= MAX; i++){
        fac.push(fac[i - 1] * i % MOD);
        inv.push(MOD - kakeruR(inv[MOD%i], (MOD / i | 0), MOD, C2) % MOD);
        finv.push(kakeruR(finv[i - 1],inv[i] ,MOD, C2));
    }
    //二項係数計算
    for (var i = 0; i <= k; i++){
    v_ans.push(kakeruR(kakeruR(fac[MAX] , finv[MAX - i],MOD, C2), finv[i], MOD, C2));
    }
    return v_ans;
}


function fastRuijoR(a, b, C, C2){
    var ans = 1;
    var binary = b.toString(2);
    var l = binary.length;
    var tmp = a;
    for (var i = 0; i < l; i++){
        if (binary.substr((i + 1) * -1, 1) === '1') ans = kakeruR(ans, tmp, C, C2);
    tmp = kakeruR(tmp, tmp, C, C2);
    }
    return ans;
}

Main(require("fs").readFileSync("/dev/stdin", "utf8")); 