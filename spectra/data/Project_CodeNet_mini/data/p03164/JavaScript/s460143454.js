function Main(input) {
    input = input.trim().split("\n").map(function(x) { return x.split(" ")});
    let N = parseInt(input[0][0], 10);
    let W = parseInt(input[0][1], 10);
    let arr_wv = [];
    for (let i = 0; i < N; i++){
        arr_wv.push(input[i + 1].map(e => parseInt(e, 10)));
    }
    
    let DP = [Array.from({length: 1e3 * N + 1}, () => Infinity)];
    DP[0][0] = 0;
    let tmpline;
    for (let i = 0; i < N; i++){
        tmpline = arr_wv[i];
        DP.push([]);
        for (let j = 0; j < tmpline[1]; j++){
            DP[i + 1].push(DP[i][j]);
        }
        for (let j = tmpline[1]; j < DP[0].length; j++){
            DP[i + 1].push(Math.min(DP[i][j],  DP[i][j - tmpline[1]] + tmpline[0]));
        }
    }

    let x = DP.pop();
    let ans = 0;
    for (let i = x.length - 1; i >= 0; i--){
        if (x[i] <= W) {
            ans = i;
            break;
        }
    }
    console.log(ans);
}


Main(require("fs").readFileSync("/dev/stdin", "utf8"));
