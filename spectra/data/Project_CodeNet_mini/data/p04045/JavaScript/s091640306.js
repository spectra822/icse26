function Main(input) {
  input=input.split("\n");
  var string=input[0].split(" ")[0];
  var output="";
  var hate=input[1].split(" ");
  var i=string-0;
  var temp;
  while(true){
    //console.log(i);
    temp=(i+"").split('');
    if(temp.every(e=>{return !hate.includes(e);})){
      console.log(i);
      return;
    }
    i++;
  }
}

//*この行以降は編集しないでください（標準入出力から一度に読み込み、Mainを呼び出します）
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
  
  