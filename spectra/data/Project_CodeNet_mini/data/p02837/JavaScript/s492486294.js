//Don't have to see. start------------------------------------------
var read = require('readline').createInterface({
  input: process.stdin, output: process.stdout
});
var obj; var inLine = [];
read.on('line', function(input){inLine.push(input);});
read.on('close', function(){
  obj = init(inLine);
  console.error('\n');
  var start = Date.now();
  Main();
  var end = Date.now() - start;
  myerr('time : ' + end + 'ms');
  myerr('memory : ' + Math.round(process.memoryUsage().heapTotal / 1024) + 'KB');
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
  var N = nextInt();
  var list = new Array(N);
  for(var i = 0; i < N; i++){
  	var Ai = nextInt();
  	list[i] = {
  		check : []
  	};
  	for(var j = 0; j < Ai; j++){
  		var tmp = nextIntArray();
  		list[i].check.push([tmp[0] - 1, tmp[1]]);
  	}
  }
  var max = 0;
  for(var i = 0; i < (1 << N); i++){
  	var selected = [];
    for(var j = 0; j < N; j++){
      if((i & (1 << j)) != 0){
        selected.push(j);
      }
    }
    var count = selected.length;
    var isOK = true;
    for(var j = 0; j < selected.length; j++){
    	var tmpcheck = list[selected[j]].check;
    	for(var k = 0; k < tmpcheck.length; k++){
    		if(tmpcheck[k][1] == 0){
    			if(selected.indexOf(tmpcheck[k][0]) != -1){
    				isOK = false;
    				break;
    			}
    		}else{
    			if(selected.indexOf(tmpcheck[k][0]) == -1){
    				isOK = false;
    				break;
    			}
    		}
    	}
    }
    if(isOK){
    	max = Math.max(max, count);
    }
  }
  myout(max);
}