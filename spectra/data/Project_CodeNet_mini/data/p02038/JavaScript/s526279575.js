var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var n=arr.shift();
var str=arr.shift();
str=str.replace(/ /g,"");
while(str.length!=1){
   str=str.replace(/../,function(s){
      if(s=="TT")return "T";
      if(s=="TF")return "F";
      if(s=="FT")return "T";
      if(s=="FF")return "T";
   });
}
console.log(str);
