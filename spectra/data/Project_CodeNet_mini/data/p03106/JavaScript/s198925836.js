const { reverse } = require("dns");

const main = stdin => {
    const input = stdin.trim().split('\n')
    //ここにかく
    //A円で一回聞ける
    const A = parseInt(input[0].split(" ")[0]);
    //所持金
    const B = parseInt(input[0].split(" ")[1]);
    //最大値Cと比較
    const K = parseInt(input[0].split(" ")[2]);
    
    let Aresults = [];
    for (let i=1; i<=A; i++){
        if(A%i == 0){
            Aresults.push(i);
        }
    }
    let ABresults = [];
    for(let i=0; i<Aresults.length; i++){
        if(B%Aresults[i] == 0){
            ABresults.push(Aresults[i])
        }
        
    }
    const ABresults2 = ABresults.reverse();
    console.log(ABresults2[K-1]);
    }
    // 標準入力
    main(require("fs").readFileSync("/dev/stdin", "utf8"))