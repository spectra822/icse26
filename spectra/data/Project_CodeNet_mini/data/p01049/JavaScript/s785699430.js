var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr= input.trim().split("\n");
var n=arr.shift()-0;
var [a,d]=arr.shift().split(" ").map(Number);
var obj={};
var m=arr.shift()-0;
for(var i=0;i<m;i++){
   var [x,y,z] = arr.shift().split(" ");
   if(x=="0"){
      if(obj.hasOwnProperty(y)==false && obj.hasOwnProperty(z)==false){
         obj[y]=z;
         obj[z]=y;
      }else if(obj.hasOwnProperty(y)==true && obj.hasOwnProperty(z)==false){
         obj[z]=obj[y];
         obj[y]=z;
      }else if(obj.hasOwnProperty(y)==false && obj.hasOwnProperty(z)==true){
         obj[y]=obj[z];
         obj[z]=y;
      } else{
         [obj[y],obj[z]]=[obj[z],obj[y]]
      }
   }else{
      if(obj.hasOwnProperty(y)==false && obj.hasOwnProperty(z)==false){
         obj[y]=z;
      }else if(obj.hasOwnProperty(y)==true && obj.hasOwnProperty(z)==false){
         obj[y]=z;
      }else if(obj.hasOwnProperty(y)==false && obj.hasOwnProperty(z)==true){
         obj[y]=obj[z];
      } else{
         obj[y]=obj[z];
      }
   }
}
var k=arr.shift();
if(obj.hasOwnProperty(k))k=obj[k];
k=k-0;
console.log(a+((k-1)*d));
