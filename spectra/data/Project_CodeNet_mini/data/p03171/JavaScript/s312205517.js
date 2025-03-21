function Main(input) {
	input = input.trim().split("\n").map(function(x) { return x.split(" ")});
	let N = parseInt(input[0][0], 10);
	a = input[1].map(e => parseInt(e, 10));
	kukanDP = Array.from({length: N}, () => []);

	console.log(DP(0, N - 1));
}

function DP(l, r){
	if (kukanDP[l][r] != null) return kukanDP[l][r];
	if (r === l + 1) {
		kukanDP[l][r] = Math.abs(a[l] - a[r]);
		return kukanDP[l][r];
	}
	if (r === l){
		kukanDP[l][r] = a[l];
		return kukanDP[l][r];
	}
	let tmp1 = a[l] - DP(l + 1, r);
	let tmp2 = a[r] - DP(l, r - 1);
	kukanDP[l][r] = Math.max(tmp1 ,tmp2);
	return kukanDP[l][r];
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
