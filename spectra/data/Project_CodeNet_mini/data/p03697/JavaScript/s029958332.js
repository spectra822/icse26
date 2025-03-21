let [a, b] = require("fs").readFileSync("/dev/stdin", "utf8").split(" ").map(Number);
console.log(a + b >= 10 ? "error" : a + b);