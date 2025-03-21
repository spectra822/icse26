function bomb(str){
   min=Math.min(min,str.length);
   for(var i=0;i<str.length;i++){
      if(str[i]==str[i+4]){
         var arr=str.split("");
         arr[i]="";
         arr[i+4]="";
         bomb(arr.join(""));
      }
      if(i!=3 && i!=7 && i!=11 && i!=15){
         if(str[i]==str[i+1]){
            var arr=str.split("");
            arr[i]="";
            arr[i+1]="";
            bomb(arr.join(""));
         }
         if(str[i]==str[i+5]){
            var arr=str.split("");
            arr[i]="";
            arr[i+5]="";
            bomb(arr.join(""));
         }
      }
      if(i!=0 && i!=4 && i!=8 && i!=12){
         if(str[i]==str[i+3]){
            var arr=str.split("");
            arr[i]="";
            arr[i+3]="";
           bomb(arr.join(""));
         }
      }
   }
}
var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var arr=input.trim().split("\n");
var n=arr.shift()-0;
while(n--){
   var str="";
   for(var i=0;i<5;i++)str+=arr.shift();
   str=str.replace(/ /g,"");
   var min=20;
   bomb(str);
   console.log(min);
}