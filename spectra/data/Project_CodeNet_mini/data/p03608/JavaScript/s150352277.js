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
  var R = one[2];
  var max = Math.pow(10,12);
  var kyori = new Array(N);
  for(var i = 0; i < N; i++){
    kyori[i] = new Array(N);
  }
  
  //移動パターンの全探索用
  var travel = myconv(next(),4);
  for(var i = 0; i < R; i++){
    travel[i]--;
  }
  
  for(var i = 0; i < M; i++){
    var tmp = myconv(next(),4);
    kyori[tmp[0] - 1][tmp[1] - 1] = tmp[2];
    kyori[tmp[1] - 1][tmp[0] - 1] = tmp[2];
  }
  
  for(var i = 0; i < N; i++){
    for(var j = 0; j < N; j++){
      /*if(i == j){
         kyori[i][j] = 0;
        continue;
      }*/
      if(kyori[i][j] == null){
         kyori[i][j] = max;
      }
    }
  }
  for(var k = 0; k < N; k++){
    for(var i = 0; i < N; i++){
      for(var j = 0; j < N; j++){
        if(kyori[i][j] > kyori[i][k] + kyori[k][j]){
           kyori[i][j] = kyori[i][k] + kyori[k][j];
        }
      }
    }
  }
  var output = max;
  for(var i = 0; i < R; i++){
    dfs(travel[i],new Set(travel),0);
  }
  myout(output);
  function dfs(parent,set,moved){
    var tmpSet = new Set(set);
    tmpSet.delete(parent);
    if(tmpSet.size == 0){
      output = Math.min(output,moved); 
      return;
    }
    var nextTravel = Array.from(tmpSet);
    for(var i = 0; i < nextTravel.length; i++){
      if(nextTravel[i] == parent){
         continue;
      }
      dfs(nextTravel[i],tmpSet,(moved + kyori[parent][nextTravel[i]]));
    }
  }
}