let [x, a, b] = require("fs").readFileSync("/dev/stdin", "utf8").split("\n").map(Number);
console.log((x - a) % b);
