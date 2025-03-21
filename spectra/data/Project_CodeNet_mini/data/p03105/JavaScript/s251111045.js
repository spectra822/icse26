const main = stdin => {
    const input = stdin.trim().split('\n')
    //ここにかく
    //A円で一回聞ける
    const A = parseInt(input[0].split(" ")[0]);
    //所持金
    const B = parseInt(input[0].split(" ")[1]);
    //最大値Cと比較
    const C = parseInt(input[0].split(" ")[2]);
    
    const sound = Math.floor(B/A);
    let Maxsound;
    if (sound < C){
        Maxsound = sound;
    } else {
        Maxsound = C;
    }
    console.log(Maxsound);
    }
    // 標準入力
    main(require("fs").readFileSync("/dev/stdin", "utf8"))