function myin(){return require("fs").readFileSync("/dev/stdin", "utf8").trim();}
function myout(t){console.log(t);}//standard output
function myerr(t){console.error(t);}//standard error
//[no]param
//0:何もしない  1:数値へ変換  2:半角SPで分割  3:改行で分割  4:半角SPで分割し、数値配列へ
//5:改行で分割し、数値配列へ  6:1文字に分割  7:1文字に分割し、数値配列へ
function myconv(i,no){switch(no){case 0:return i;case 1:return parseInt(i);case 2:return i.split(" ");case 3:return i.split("\n");case 4:return i.split(" ").map((a)=>Number(a));case 5:return i.split("\n").map((a)=>Number(a));case 6:return i.split("");case 7:return i.split("").map((a)=>Number(a));}}
function Main(input) {
  input = myconv(input,4);
  var N = input[0];
  var P = input[1];
  if(isPrime(P)){
     myout(1);
    return;
  }
  var pf = getPrimeFactorization(P);
  var pfKeys = Array.from(Object.keys(pf));
  var output = 1;
  for(var i = 0; i < pfKeys.length; i++){
    if(pf[pfKeys[i]] >= N){
       output *= Math.pow(pfKeys[i],Math.floor(pf[pfKeys[i]] / N));
    }
  }
  myerr(pf);
  myout(output);
}
function getPrimeFactorization(val){
  var primeList = {};
  var div = 2;
  while(val != 1){
    if(val % div == 0){
      (primeList[div] == null)  ? primeList[div] = 1 : primeList[div]++;
      val /= div;
      if(isPrime(val)){
        (primeList[val] == null)  ? primeList[val] = 1 : primeList[val]++;
        break;
      }
    }else{
      div = (div == 2) ? div + 1 : div + 2;
    }
  }
  return primeList;
}
function isPrime(val){
        if(val <= 1 || (val != 2 && val % 2 == 0)){
                return false;
        }else if(val == 2){
                return true;
        }
        var root = Math.floor(Math.sqrt(val));
        for(var i = 3; i <= root; i += 2){
                if(val % i == 0){
                        return false;
                }
        }
        return true;
}
Main(myin());
