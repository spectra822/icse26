var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var abc="A B C D E F G H I J K L M N O P Q R S T U V W X Y Z".split(" ");
var def="D E F G H I J K L M N O P Q R S T U V W X Y Z A B C".split(" ");
for(var i=0;i<Arr.length;i++){
var str=Arr[i];
var STR="";
for(var j=0;j<str.length;j++)STR+=abc[def.indexOf(str[j])];
console.log(STR);
}