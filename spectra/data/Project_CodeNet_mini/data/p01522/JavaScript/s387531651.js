var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var Arr=(input.trim()).split("\n");
var NK=Arr.shift().split(" ").map(Number);
var N=NK[0];
var K=NK[1];
var rabbit=[];
for(var i=0;i<N;i++)rabbit[i]=true;
var boat=[];
for(var i=0;i<K;i++){
   var v=Arr.shift().split(" ").map(function(value){return (value-0)-1;});
   v.shift();
   boat.push(v);
}
var R=Arr.shift()-0;
var PQ=[];
for(var i=0;i<R;i++){
   var v=Arr.shift().split(" ").map(function(value){return (value-0)-1;});
   PQ.push(v);
}
boat.forEach(function(v){
   PQ.forEach(function(V){
      var a=v.indexOf(V[0]);
      var b=v.indexOf(V[1]);
      if(a!==-1 && b!==-1){
         rabbit[V[0]]=false;
         rabbit[V[1]]=false;
      }
   });
});
var ans=0;
rabbit.forEach(function(v){if(!v)ans++;});
console.log(ans);