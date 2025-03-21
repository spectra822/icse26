"use strict";

const main = arg => {
    const inputList = arg.trim().split("\n");
    const N = parseInt(inputList[0].split(" ")[0]);
    const K = parseInt(inputList[0].split(" ")[1]);
    let ALightList = inputList[1].split(" ").map(ele => parseInt(ele));

    for (let i = 0; i < K; i++) {
        const imos = Array(ALightList.length).fill(0);

        for (let j = 0; j < ALightList.length; j++) {
            let minus = j - ALightList[j];
            let plus = j + ALightList[j] + 1;
            if (minus < 0) {
                minus = 0;
            }
            imos[minus]++;
            imos[plus]--;
        }
        imos.length = ALightList.length;

        for (let k = 1; k < imos.length; k++) {
            imos[k] += imos[k - 1]
        }

        if (ALightList.every((ele, idx) => ele == imos[idx])) {
            break;
        }

        ALightList = imos;
    }
    console.log(ALightList.join(" "))
}
main(require('fs').readFileSync('/dev/stdin', 'utf8'));