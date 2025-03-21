var read = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});
var obj;
var inLine = [];
read.on('line', function(input){inLine.push(input);});
read.on('close', function(){
  obj = init(inLine);
  myerr("-----start-----");
  var start = new Date();
  Main();
  var end = new Date() - start;
  myerr("----- end -----");
  myerr("time : " + (end) + "ms");
});
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
function Main(){
	var N = nextInt();
	var list = new Array(N);
	for(var i = 0; i < N; i++){
		list[i] = {
			child : new Set(),
			from : null,
			access : false,
			color : null,
			count : 0
		};
	}
	for(var i = 0; i < N - 1; i++){
		var tmp = nextIntArray();
		list[tmp[0] - 1].child.add(tmp[1] - 1);
		list[tmp[1] - 1].child.add(tmp[0] - 1);
	}
	
	var queue = new Array(100007);
	queue[0] = 0;
	list[0].access = true;
	var mae = 0;
	var ato = 1;
	while(mae != ato){
		var parent = queue[mae];
		mae++;
		if(parent == N - 1){
			break;
		}
		var child = Array.from(list[parent].child);
		for(var i = 0; i < child.length; i++){
			if(!list[child[i]].access){
				list[child[i]].access = true;
				list[child[i]].from = parent;
				queue[ato] = child[i];
				list[child[i]].count = list[parent].count + 1;
				ato++;
			}
		}
	}
	
	
	var cut = Math.ceil(list[N - 1].count / 2);
	var now = N - 1;
	while(cut != 0){
		now = list[now].from;
		cut--;
	}
	list[0].color = "BLACK";
	list[N - 1].color = "WHITE";
	list[now].color = "BLACK";
	bfs(0,"BLACK");
	bfs(N - 1,"WHITE");
	var w = 0;
	var b = 0;
	for(var i = 0; i < N; i++){
		if(list[i].color == "WHITE"){
			w++;
		}else{
			b++;
		}
	}
	if(b > w){
		myout("Fennec");
	}else{
		myout("Snuke");
	}
	function bfs(index, color){
		var queue = new Array(100007);
		var mae = 0;
		var ato = 1;
		queue[mae] = index;
		while(mae != ato){
			var parent = queue[mae];
			mae++;
			var child = Array.from(list[parent].child);
			for(var i = 0; i < child.length; i++){
				if(list[child[i]].color == null){
					queue[ato] = child[i];
					ato++;
					list[child[i]].color = color;
				}
			}
		}
	}
}
