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
  var output = new Array(N);
  for(var i = 0; i < N; i++){
    list[i] = {
    	depth : null,
      access : false,
      child : [],
      value : -1
    };
  }
  var one = 1;
  var two = 2;
  var three = 3;
  for(var i = 0; i < N - 1; i++){
    var tmp = nextIntArray();
    list[tmp[0] - 1].child.push(tmp[1] - 1);
    list[tmp[1] - 1].child.push(tmp[0] - 1);
  }
  var queue = new Array(N + 5);
  var maeIndex = 0;
  var atoIndex = 1;
  queue[0] = 0;
  list[0].access = true;
  list[0].depth = 1;
  var oddDepth = 0;
  var evenDepth = 0;
  while(maeIndex != atoIndex){
    var now = queue[maeIndex++];
    if(list[now].depth % 2 == 1){
      oddDepth++;
    }else{
      evenDepth++;
    }
    var child = list[now].child;
    for(var i = 0; i < child.length; i++){
      if(!list[child[i]].access){
        list[child[i]].access = true;
        list[child[i]].depth = list[now].depth + 1;
        queue[atoIndex++] = child[i];
      }
    }
  }
  if(oddDepth > (N / 3) && evenDepth > (N / 3)){
    for(var i = 0; i < N; i++){
      if(list[i].depth % 2 == 1){
        if(one <= N){
          list[i].value = one;
          one += 3;
        }
      }else{
        if(two <= N){
          list[i].value = two;
          two += 3;
        }
      }
    }
  }else{
    for(var i = 0; i < N; i++){
      if(oddDepth < evenDepth){
        if(list[i].depth % 2 == 1){
          list[i].value = three;
          three += 3;
        }
      }else{
        if(list[i].depth % 2 == 0){
          list[i].value = three;
          three += 3;
        }
      }
    }
  }
  for(var i = 0; i < N; i++){
    if(list[i].value == -1){
      if(one <= N){
        list[i].value = one;
        one += 3;
      }else if(two <= N){
        list[i].value = two;
        two += 3;
      }else if(three <= N){
        list[i].value = three;
        three += 3;
      }
    }
    output[i] = list[i].value;
  }
  myout(myconv(output, 8));
}
