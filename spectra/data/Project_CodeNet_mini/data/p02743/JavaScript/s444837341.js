function Main(input) {
 
	// 1行目がinput[0], 2行目がinput[1], …に入る
	input = input.split("\n");
  
    let a = BigInt(input[0].split(" ")[0])
    let b = BigInt(input[0].split(" ")[1])
    let c = BigInt(input[0].split(" ")[2])
  
    let num = a ** 2n + b ** 2n + c ** 2n - (2n * a * b) - (2n * b * c) - (2n * c * a);
    
    if ((c - a - b) > 0 && num > 0) console.log("Yes")
    else console.log("No")
    
}
//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));