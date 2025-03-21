var GET=(function(){function f(s){return new g(s);}function g(s){this._s=s.trim().split("\n");this._y=0;}g.prototype.a=function(f){var s=this._s, y=this._y, r;if(typeof s[y]==="string")s[y]=s[y].split(" ").reverse();r=s[y].pop();if(!s[y].length)this._y++;return f?r:+r;};g.prototype.l=function(f){var s=this._s[this._y++].split(" ");return f?s:s.map(a=>+a);};g.prototype.m=function(n,f){var r=this._s.slice(this._y,this._y+=n).map(a=>a.split(" "));return f?r:r.map(a=>a.map(a=>+a));};g.prototype.r=function(n,f){var r=this._s.slice(this._y,this._y+=n);return f?r:r.map(a=>+a);};return f;})();
var o=GET(require("fs").readFileSync("/dev/stdin","utf8"));
function xArray(v){var a=arguments,l=a.length,r="Array(a["+--l+"]).fill(0).map(x=>{return "+v+";})";while(--l)r="Array(a["+l+"]).fill(0).map(x=>"+r+")";return eval(r);}
var mod = 998244353;
function abmod(){for(var a=arguments,r=a[0],i=1;i<a.length;)r=((r>>16)*a[i]%mod*65536+(r&65535)*a[i++])%mod;return r;}
var BIT = (function(){
  function f(n){return new BIT(n);}
  function BIT(n){
    this.a = Array(n+1).fill(0);
  }
  BIT.prototype.add = function(x,i){
    for(;i<this.a.length;i+=i&-i)this.a[i]+=x;
  };
  BIT.prototype.get = function(i){
    for(var r=0;i;i-=i&-i)r+=this.a[i];
    return r;
  };
  return f;
})();

console.log(main());
function main(){
  var n = o.a();
  var x = o.m(n).sort((a,b)=>a[1]-b[1]);
  var p2 = [1]; p2.length = n+1;
  for(var i = 0; i < n; i++){
    x[i][1] = i+1;
    p2[i+1] = p2[i] << 1;
    if(p2[i+1] >= mod)p2[i+1] -= mod;
  }
  x.sort((a,b)=>a[0]-b[0]);
  var bitL = BIT(n), bitR = BIT(n);
  var xy = xArray(0,n,4);
  for(i = 0; i < n; i++){
    xy[i][2] = bitL.get(x[i][1]);
    xy[i][3] = i-xy[i][2];
    bitL.add(1,x[i][1]);
  }
  for(i = n; i--;){
    xy[i][1] = bitR.get(x[i][1]);
    xy[i][0] = n-i-1-xy[i][1];
    bitR.add(1,x[i][1]);
  }
  var ans = abmod(n,p2[n-1]);
  for(i = 0; i < n; i++){
    var t = xy[i];
    ans += abmod(p2[t[3]]-1,p2[t[1]]-1,p2[t[0]],p2[t[2]]);
    ans += abmod(p2[t[0]]-1,p2[t[2]]-1,p2[t[1]]+p2[t[3]]-1);
  }
  return ans%mod;
}