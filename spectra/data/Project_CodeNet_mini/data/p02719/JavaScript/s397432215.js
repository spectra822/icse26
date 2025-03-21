"use strict";

const main = (input) => {
    const spi = input.split('\n');
    const [n, k] = spi[0].split(' ').map(e => BigInt(e));

    const a1 = n % k;
    const a2 = a1 - k < 0 ? -(a1 - k) : a1 - k;

    console.log((a1 <= a2 ? a1 : a2).toString());
};

main(require("fs").readFileSync("/dev/stdin", "utf8"));
