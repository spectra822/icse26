function Main(input) {
    input = input.trim().split("\n").map(function(x) { return x.split(" ")});    

    let s = input[0][0].split("");
    let t = input[1][0].split("");


    var arr_dp = [];
    for (var j = 0; j <= t.length; j++){
        arr_dp.push([]);
        arr_dp[j][0] = 0;
    }
    for (var i = 0; i <= s.length; i++){
        arr_dp[0][i] = 0;
    }
    for (var j = 0; j < t.length; j++){
        for (var i = 0; i < s.length; i++){
            if (s[i] === t[j]) arr_dp[j + 1][i + 1] = arr_dp[j][i] + 1;
            else arr_dp[j + 1][i + 1] = Math.max(arr_dp[j + 1][i], arr_dp[j][i + 1]);
        }
    }
	let l = arr_dp[t.length][s.length];
	let tmpLocation1 = t.length;
	let tmpLocation2 = s.length;
	let tmpCharacter;
	let v_ans = [];
	for (let i = 0; i < l; i++){
		for (let j = tmpLocation2; j >= 1 ; j--){
			if (arr_dp[tmpLocation1][j] > arr_dp[tmpLocation1][j - 1]){
				tmpLocation2 = j - 1;
				break;
			}
		}
		tmpCharacter = s[tmpLocation2];
		for  (let j = tmpLocation1; j >= 1; j--){
			if (t[j - 1] === tmpCharacter){
				v_ans.push(tmpCharacter);
				tmpLocation1 = j - 1;
				break;
			}
		}
	}
	console.log(v_ans.reverse().join(""));
}

Main(require("fs").readFileSync("/dev/stdin", "utf8"));