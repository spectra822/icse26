let l = require("fs").readFileSync("/dev/stdin", "utf8").split(" ");
[x, y] = l.map(i => new Date(2000, Number(i), 0).getDate());
console.log(x == y ? "Yes" : "No");