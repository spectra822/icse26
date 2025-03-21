var input = require("fs").readFileSync("/dev/stdin", "utf8").trim().split("\n");
var obj = {
  "list" : input,
  "index" : 0,
  "max" : input.length,
  "next" : function(){
    if(!this.hasNext()){throw "NoSuchElementException:次に要素は無いよ";}
    var returnObj = this.list[this.index];
    this.index++;
    return returnObj;
  },
  "hasNext" : function(){return (this.index < this.max);}
}
Main();
function next(){return obj.next();}
function hasNext(){return obj.hasNext();}
function myout(t){console.log(t);}//standard output
function myerr(t){console.error(t);}//standard error
//[no]要素の扱い。数値型
//不明値、異常時:引数そのまま返す　1:数値へ変換
//2:半角SPで分割 4:半角SPで分割し、数値配列へ
//6:1文字で分割  7:1文字で分割し、数値配列へ
//8:半角SPで結合 9:改行で結合 0:文字なしで結合
function myconv(i,no){try{switch(no){case 1:return parseInt(i);case 2:return i.split(" ");case 4:return i.split(" ").map((a)=>Number(a));case 6:return i.split("");case 7:return i.split("").map((a)=>Number(a));case 8:return i.join(" ");case 9:return i.join("\n");case 0:return i.join("");default:return i;}}catch(e){return i;}}
function Main(){
  var one = myconv(next(),4);
  var N = one[0];
  var M = one[1];
  var kyori = new Array(N);
  kyori[0] = 0;
  var max = Math.pow(10,14);
  for(var i = 1; i < N; i++){
    kyori[i] = max;
  }
  var alist = new Array(M);
  var blist = new Array(M);
  var clist = new Array(M);
  for(var i = 0; i < M; i++){
    var tmp = myconv(next(),4);
    alist[i] = tmp[0] - 1;
    blist[i] = tmp[1] - 1;
    clist[i] = tmp[2] * (-1);
  }
  for(var i = 0; i < N - 1; i++){
    for(var j = 0; j < M; j++){
      if(kyori[alist[j]] == max){
         continue;
      }
      //a→bに向かうとき、すでに分かってる距離(∞含む)よりも短いなら更新
      if(kyori[blist[j]] > kyori[alist[j]] + clist[j]){
         kyori[blist[j]] = kyori[alist[j]] + clist[j];
      }
    }
  }
  //負閉路(無限に距離を減らせるような場所)があるか
  var negative = new Array(N).fill(false);
  for(var i = 0; i < N; i++){
    for(var j = 0; j < M; j++){
      if(kyori[alist[j]] == max){
         continue;
      }
      //最初の経路探索が終わった後に、さらに短いところが見つかれば負経路
      if(kyori[blist[j]] > kyori[alist[j]] + clist[j]){
         kyori[blist[j]] = kyori[alist[j]] + clist[j];
         negative[blist[j]] = true;
      }
      if(negative[alist[j]]){
         negative[blist[j]] = true;
      }
    }
  }
  if(negative[N - 1]){
     myout("inf");
  }else{
     myout(kyori[N - 1] * (-1));
  }
}