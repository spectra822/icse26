const main = input => {
  const [A, P] = input.trim().split(' ').map(x => parseInt(x))
  console.log(Math.floor((3 * A + P) / 2))

}
// 標準入力
main(require("fs").readFileSync("/dev/stdin", "utf8"));
