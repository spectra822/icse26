function Main(input) {
	input = input.trim().split("\n").map(function(x) { return x.split(" ")});
	let N = parseInt(input[0][0], 10);
	let K = parseInt(input[0][1], 10);
	let a = input[1].map(e => parseInt(e, 10));
	let aCheck = Array.from({length:1e5 + 1},() => false);
	for (x of a){
		aCheck[x] = true;
	}
	let DP = Array.from({length: K + 1}, () => 0);
	//2なら後攻の勝利、1なら先攻の勝利
	DP[0] = 2;
	for (let i = 1; i <= K; i++){
		DP[i] = 2;
		for (let x of a){
			if (x > i) break;
			if (DP[i - x] === 2) {
				DP[i] = 1;
				break;
			}
		}
	}
	if (DP.pop() === 1) console.log("First");
	else console.log("Second");

}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
