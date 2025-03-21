function Main(input) {
  const row = input.split(" ");
    	let X = parseInt(row[0], 10);
    	let K = parseInt(row[1], 10);
    	const D = parseInt(row[2], 10);
    let absX = Math.abs(X);
    let a = Math.floor(absX / D);//往復開始地点までにかかる回数
    let ans;

    if((absX /D) >= K) {
       ans = absX - D * K;

    } else {
    let K2 = K - a;
       absX = absX % D;//余りが0に最も近い座標
       if(K2 % 2 === 0) {
    　ans = absX;
      } else {
         ans = absX - D;
      }
    } console.log(Math.abs(ans));
}

Main(require("fs").readFileSync("/dev/stdin", "utf8"));
