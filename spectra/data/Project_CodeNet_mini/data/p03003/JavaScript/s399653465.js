var GET=(function(){function f(s){return new g(s);}function g(s){this._s=s.trim().split("\n");this._y=0;}g.prototype.a=function(f){var s=this._s, y=this._y, r;if(typeof s[y]==="string")s[y]=s[y].split(" ").reverse();r=s[y].pop();if(!s[y].length)this._y++;return f?r:+r;};g.prototype.l=function(f){var s=this._s[this._y++].split(" ");return f?s:s.map(a=>+a);};g.prototype.m=function(n,f){var r=this._s.slice(this._y,this._y+=n).map(a=>a.split(" "));return f?r:r.map(a=>a.map(a=>+a));};g.prototype.r=function(n,f){var r=this._s.slice(this._y,this._y+=n);return f?r:r.map(a=>+a);};return f;})();
var o=GET(require("fs").readFileSync("/dev/stdin","utf8"));
function xArray(v){var a=arguments,l=a.length,r="Array(a["+--l+"]).fill(0).map(x=>{return "+v+";})";while(--l)r="Array(a["+l+"]).fill(0).map(x=>"+r+")";return eval(r);}
var mod = 1e9+7;

console.log(main());
function main(){
  var n = o.a();
  var m = o.a();
  var s = o.l();
  var t = o.l();
  var dp = xArray(0,n+1,m+1);
  var ans = 1;
  for(var i = 0; i < n; i++){
    var x = 0;
    for(var j = 0; j < m; j++){
      if(s[i] === t[j]){
        x += dp[i][j]+1;
        ans += dp[i][j]+1;
        ans %= mod;
        dp[i+1][j+1] = dp[i+1][j]+dp[i][j+1]+1;
      }else{
        dp[i+1][j+1] = x+dp[i][j+1];
      }
      dp[i+1][j+1] %= mod;
    }
  }
  return ans;
}