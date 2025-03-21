function Main(input) {
	input = input.trim().split("\n").map(function(x) { return x.split(" ")});
	let N = parseInt(input[0][0], 10);
	a = input[1] .map(e => parseInt(e, 10));
	DP = Array.from({length: N}, () => []);
	ruisekiwa = [0];
	for (let i = 0; i < N; i++) ruisekiwa.push(ruisekiwa[i] + a[i]);
	console.log(kukanDP(0, N - 1))
}

function kukanDP(l, r){
	if (DP[l][r] != null) return DP[l][r];
	if (l === r) {
		DP[l][r] = 0;
		return 0;
	}
	if (r === l + 1){
		DP[l][r] = a[l] + a[r];
		return DP[l][r];
	}
	let tmp = Infinity;
	for (let i = l; i < r; i++){
		tmp = Math.min(tmp, kukanDP(l, i) + kukanDP(i + 1, r) - ruisekiwa[l] + ruisekiwa[r + 1]);
	}
	DP[l][r] = tmp;
	return tmp;
}

Main(require("fs").readFileSync("/dev/stdin", "utf8"));
