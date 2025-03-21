//Don't have to see. start------------------------------------------
var read = require('readline').createInterface({
  input: process.stdin, output: process.stdout
});
var obj; var inLine = [];
read.on('line', function(input){inLine.push(input);});
read.on('close', function(){
  obj = init(inLine);
  console.error('\n↑入力 ↓出力');
  Main();
});
function makeClone(obj){return (obj instanceof Set) ? new Set(Array.from(obj)) : JSON.parse(JSON.stringify(obj));}
function nextInt(){return myconv(next(),1);} function nextStrArray(){return myconv(next(),2);}
function nextIntArray(){return myconv(next(),4);} function nextCharArray(){return myconv(next(),6);}
function next(){return obj.next();} function hasNext(){return obj.hasNext();}
function init(input){  
  return {
    list : input, index : 0, max : input.length,
    hasNext : function(){return (this.index < this.max);},
    next : function(){if(this.hasNext()){return this.list[this.index++];}else{throw 'ArrayIndexOutOfBoundsException ‚There is no more input';}}
  };
}
function myout(s){console.log(s);}
function myerr(s){console.error('debug:' + require('util').inspect(s,false,null));}
//param "no" is
//unknown or outlier : return i. 1: parseInt.
//2: split space. 4: split space and parseInt.
//6: split 1 character. 7: split 1 character and parseInt.
//8: join space. 9: join nextline. 0: join no character.
function myconv(i,no){try{switch(no){case 1:return parseInt(i);case 2:return i.split(' ');case 4:return i.split(' ').map(Number);case 6:return i.split('');case 7:return i.split('').map(Number);case 8:return i.join(' ');case 9:return i.join('\n');case 0:return i.join('');default:return i;}}catch(e){return i;}}

//Don't have to see. end------------------------------------------
function Main(){
  var one = nextIntArray();
  var N = one[0];
  var K = one[1];
  var L = one[2];
  var ufk = unionFind(N);
  var ufl = unionFind(N);
  var output = new Array(N);
  var klist = new Array(K);
  var llist = new Array(L);
  for(var i = 0; i < K; i++){
    var tmp = nextIntArray();
    tmp.sort();
    tmp[0]--;
    tmp[1]--;
    klist[i] = tmp;
    ufk.doUnion(tmp[0], tmp[1]);
  }
  for(var i = 0; i < L; i++){
    var tmp = nextIntArray();
    tmp.sort();
    tmp[0]--;
    tmp[1]--;
    llist[i] = tmp;
    ufl.doUnion(tmp[0], tmp[1]);
  }
  var map = {};
  for(var i = 0; i < N; i++){
    var rt = ufl.getRootIndex(i) + ":" + ufk.getRootIndex(i);
    if(map[rt] == null){
      map[rt] = 0;
    }
    map[rt]++;
  }
  for(var i = 0; i < N; i++){
    output[i] = map[ufl.getRootIndex(i) + ":" + ufk.getRootIndex(i)];
  }
  myout(myconv(output, 8));
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