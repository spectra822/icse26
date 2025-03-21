function myin(){return require("fs").readFileSync("/dev/stdin", "utf8").trim();}
function myout(t){console.log(t);}//standard output
function myerr(t){console.log(t);}//standard error
//[no]param
//0:何もしない  1:数値へ変換  2:半角SPで分割  3:改行で分割  4:半角SPで分割し、数値配列へ
//5:改行で分割し、数値配列へ  6:1文字に分割  7:1文字に分割し、数値配列へ
function myconv(i,no){switch(no){case 0:return i;case 1:return parseInt(i);case 2:return i.split(" ");case 3:return i.split("\n");case 4:return i.split(" ").map((a)=>Number(a));case 5:return i.split("\n").map((a)=>Number(a));case 6:return i.split("");case 7:return i.split("").map((a)=>Number(a));}}

function Main(input) {
  input = myconv(input,1);
  var primeCountList = {
  	"1" : 1
  };
  for(var i = 1; i <= input; i++){
    var tmpI = i;
    var div = 2;
    while(tmpI != 1){
       if(tmpI % div == 0){
         if(primeCountList[div] == null){
           primeCountList[div] = 1;
         }else{
           primeCountList[div]++;
         }
         tmpI /= div;
       }else{
         div = (div == 2) ? div+1 : div+2;
       }
    }
  }
  //myout(primeCountList);
  var primeList = Object.keys(primeCountList);
  
  var result442 = 0;//P1^4,P2^4,P3^2
  var result242 = 0;//P1^24,P3^2
  var result144 = 0;//P1^14,P2^4,
  var result74 = 0;//P1^74
  var result2 = 0;
  var result4 = 0;
  var result14 = 0;
  var result24 = 0;
  var result74 = 0;
  for(var i = 0; i < primeList.length; i++){
    if(primeCountList[primeList[i]] >= 2){
       result2++;
    }
    if(primeCountList[primeList[i]] >= 4){
       result4++;
    }
    if(primeCountList[primeList[i]] >= 14){
       result14++;
    }
    if(primeCountList[primeList[i]] >= 24){
       result24++;
    }
    if(primeCountList[primeList[i]] >= 74){
       result74++;
    }
  }
  result442 = (result4 * (result4 -1)) / 2 * (result2 -2);
  result242 = result24 * (result2 -1);
  result144 = result14 * (result4 -1);
  
  myout(result442 + result242 + result144 + result74);
  
}

function getPrimeFactorization(val){
	var primeList = {
		"1" : 1
	};
	var div = 2;
	while(val != 1){
		if(val % div == 0){
			if(primeList[div] == null){
				primeList[div] = 1;
			}else{
				primeList[div]++;
			}
			val /= div;
		}else{
			div = (div == 2) ? div+1 : div+2;
		}
    }
  return primeList;
}

for(var i = 1; i <= 10; i++){
  //Main(i);
}

Main(myin());
