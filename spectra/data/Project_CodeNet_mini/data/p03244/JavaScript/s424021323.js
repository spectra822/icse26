function myin(){return require("fs").readFileSync("/dev/stdin", "utf8").trim();}
function myout(t){console.log(t);}//standard output
function myerr(t){console.error(t);}//standard error
//[no]param
//0:何もしない  1:数値へ変換  2:半角SPで分割  3:改行で分割  4:半角SPで分割し、数値配列へ
//5:改行で分割し、数値配列へ  6:1文字に分割  7:1文字に分割し、数値配列へ
function myconv(i,no){switch(no){case 0:return i;case 1:return parseInt(i);case 2:return i.split(" ");case 3:return i.split("\n");case 4:return i.split(" ").map((a)=>Number(a));case 5:return i.split("\n").map((a)=>Number(a));case 6:return i.split("");case 7:return i.split("").map((a)=>Number(a));}}
function Main(input) {
  input = myconv(input,3);
  var N = myconv(input[0],1);
  var list = myconv(input[1],2);
  var oddlist = {};
  var evenlist = {};
  for(var i = 0; i < N; i++){
    //偶奇が一致するところだけ関係する
    if(i % 2 == 0){
       if(oddlist[list[i]] == null){
     	  oddlist[list[i]] = 1;
    	}else{
    	   	oddlist[list[i]]++;
    	}
    }else{
       if(evenlist[list[i]] == null){
     	  evenlist[list[i]] = 1;
  	  }else{
   	  	 evenlist[list[i]]++;
  	  }
    }
  }
  
  var output = 0;
  var oddSet = Object.keys(oddlist);
  var evenSet = Object.keys(evenlist);
  if(oddSet.length == 1 && evenSet.length == 1){
    if(evenSet[0] == oddSet[0]){
       myout(N/2);
    	return;
    }else{
       myout(0);
      return;
    }
    
  }
  var tmp = 0;
  var lastSelect = "";
  oddSet.sort(function(a,b){
  	return oddlist[b] - oddlist[a];
  });
  evenSet.sort(function(a,b){
  	return evenlist[b] - evenlist[a];
  });
  
  if(oddSet[0] == evenSet[0]){
    var mae = 10000000;
    var ato = 10000000;
     if(oddSet[1] != null){
        mae = (N / 2 - oddlist[oddSet[1]]) + (N / 2 - evenlist[evenSet[0]]);
     }
     if(evenSet[1] != null){
        ato = (N / 2 - oddlist[oddSet[0]]) + (N / 2 - evenlist[evenSet[1]]);
     }
    output = Math.min(mae,ato);
  }else{
     output = (N / 2 - oddlist[oddSet[0]]) + (N / 2 - evenlist[evenSet[0]]);
  }
  myout(output);
  
}
Main(myin());
