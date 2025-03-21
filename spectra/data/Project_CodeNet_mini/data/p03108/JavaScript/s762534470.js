//↓見なくていいよ！ここから--------------------------------------------------
var read = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
var obj;
var inLine = [];
read.on('line', function(input){inLine.push(input);});
read.on('close', function(){
  obj = init(inLine);
  console.error("\n");
  var start = Date.now();
  Main();
  var end = Date.now() - start;
  myerr("time : " + (end) + "ms");
  myerr("memory : " + Math.round(process.memoryUsage().heapTotal / 1024) + "KB");
});
function makeClone(obj){return JSON.parse(JSON.stringify(obj));}
function nextInt(){return myconv(next(),1);} function nextStrArray(){return myconv(next(),2);}
function nextIntArray(){return myconv(next(),4);} function nextCharArray(){return myconv(next(),6);}
function next(){return obj.next();} function hasNext(){return obj.hasNext();}
function init(input){  
  var returnObj = {
    list : input, index : 0, max : input.length,
    hasNext : function(){return (this.index < this.max);},
    next : function(){if(!this.hasNext()){throw "ArrayIndexOutOfBoundsException これ以上ないよ";}else{var returnInput = this.list[this.index];this.index++;return returnInput;}}
  };
  return returnObj;
}
function myout(s){console.log(s);}
function myerr(s){console.error("debug:" + require("util").inspect(s,false,null));}
//[no]要素の扱い。数値型
//不明値、異常時:引数そのまま返す 1:数値へ変換
//2:半角SPで分割 4:半角SPで分割し、数値配列へ
//6:1文字で分割  7:1文字で分割し、数値配列へ
//8:半角SPで結合 9:改行で結合 0:文字なしで結合
function myconv(i,no){try{switch(no){case 1:return parseInt(i);case 2:return i.split(" ");case 4:return i.split(" ").map(Number);case 6:return i.split("");case 7:return i.split("").map(Number);case 8:return i.join(" ");case 9:return i.join("\n");case 0:return i.join("");default:return i;}}catch(e){return i;}}

//↑見なくていいよ！ここまで--------------------------------------------------
function Main(){
	var one = nextIntArray();
	var N = one[0];
	var M = one[1];
	var list = new Array(M);
	for(var i = 0; i < M; i++){
		list[M - i - 1] = nextIntArray();
	}
	var uf = unionFind(N);
	var output = new Array(M);
	output[M - 1] = N * (N - 1) / 2;
	for(var i = 1; i < M; i++){
		var tmp = list[i - 1];
		var L = tmp[0] - 1;
		var R = tmp[1] - 1;
		if(!uf.isSame(L,R)){
			var minus = uf.getSize(L) * uf.getSize(R);
			output[M - i - 1] = Math.max(output[M - i] - minus, 0);
			uf.doUnion(L, R);
		}else{
			output[M - i - 1] = output[M - i];
		}
	}
	myout(myconv(output,9));
}
function unionFind(n){
  var uf = {
    //全てのインデックスは「-X(親、絶対値はグループの大きさ)」「自分が属する親(≒根)」のいずれかを持つ。
    //最初はみんなグループの大きさ1の親
    "list" : new Array(n).fill(-1),
    
    //同じ親を持つか
    "isSame" : function(mae, ato){
      return this.getRootIndex(mae) == this.getRootIndex(ato);
    },
    //自身の親インデックスをたどって根っこに着く
    //親にたどり終えたら子に帰っていくついでに、子たちに「共通の親を持っている」ことを知らせる
    "getRootIndex" : function(index){
      if(this.list[index] < 0){
        return index;
      }else{
        this.list[index] = this.getRootIndex(this.list[index]);
        return this.list[index];
      }
    },
    //異なる親同士のまとまりを一つにする（同じ親ならスルー）
    //小さいグループの親が大きいグループの親の直下に着く
    //グループの大きさも更新する
    "doUnion" : function(mae, ato){
      var maeRoot = this.getRootIndex(mae);
      var atoRoot = this.getRootIndex(ato);
      if(!this.isSame(maeRoot, atoRoot)){
        if(maeRoot >= atoRoot){
          this.list[maeRoot] += this.list[atoRoot];
          this.list[atoRoot] = maeRoot;
        }else{
          this.list[atoRoot] += this.list[maeRoot];
          this.list[maeRoot] = atoRoot;
        }
      }
    },
    //「-X(親、絶対値はグループの大きさ)」
    //なので、インデックスを指定→親を知る→親の持つグループの大きさがわかる。
    //ただしマイナス値なので、掛け算して返す。
    "getSize" : function(index){
      return -this.list[this.getRootIndex(index)];
    }
  }
  return uf;
}