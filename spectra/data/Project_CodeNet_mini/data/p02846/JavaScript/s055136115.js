function Main(input) {
	input = input.trim().split("\n").map(function(x) { return x.split(" ")});
	let T1 = parseInt(input[0][0], 10);
	let T2 = parseInt(input[0][1], 10);
	let A1 = parseInt(input[1][0], 10);
	let A2 = parseInt(input[1][1], 10);
	let B1 = parseInt(input[2][0], 10);
	let B2 = parseInt(input[2][1], 10);
	
	let d1 = BigInt(A1 - B1) * BigInt(T1);
	let d2 = BigInt(A2 - B2) * BigInt(T2) + d1;

	let ans = 0n;
	let tmp;
	if (d2 === 0n) ans = 'infinity';
	else if (d1 * d2 < 0n) {
		d2 = d2 * -1n;
		tmp = (d1 / d2);
		ans = (tmp * d2 === d1) ? tmp * 2n : tmp * 2n + 1n;		
	}
	else ans = 0;
	console.log(ans.toString());
}

Main(require("fs").readFileSync("/dev/stdin", "utf8"));


