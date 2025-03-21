function Main(input) {
	input = input.split(" ").map(Number);
	var n = input[1]+input[0]+1;
	var m = Math.min(n,input[2]);
	console.log(m+input[1]);
}Main(require("fs").readFileSync("/dev/stdin", "utf8").trim());